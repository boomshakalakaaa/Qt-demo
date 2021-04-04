#include "videoshow.h"
#include "qdebug.h"

VideoShow::VideoShow()
{
    m_fileName = "D:/Kugou/华语群星 - 少林英雄.mp4";

}
void VideoShow::run()
{
    //1.初始化 FFMPEG 调用了这个才能正常使用编码器和解码器 注册所用函数
    av_register_all();
    //2.需要分配一个 AVFormatContext，FFMPEG 所有的操作都要通过这个 AVFormatContext 来进行可以理解为视频文件指针
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    //中文兼容
    std::string path = m_fileName.toStdString();
    const char* file_path = path.c_str();

    //3. 打开视频文件
    if( avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0 )
    {
        qDebug()<<"can't open file";
        return;
    }
    //3.1 获取视频文件信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        qDebug()<<"Could't find stream infomation.";
        return;
    }


    //4.读取视频流
    int videoStream = -1;
    int i;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
    }
    //如果 videoStream 为-1 说明没有找到视频流
    if (videoStream == -1)
    {
        printf("Didn't find a video stream.");
        return;
    }
    //5.查找解码器
    auto pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    auto pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL)
    {
        printf("Codec not found.");
        return;
    }
    //打开解码器
    if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("Could not open codec.");
        return;
    }
    //6.申请解码需要的结构体 AVFrame 视频缓存的结构体
    AVFrame *pFrame, *pFrameRGB;
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    //分配一个 packet
    AVPacket *packet = (AVPacket *) malloc(sizeof(AVPacket));

    //7.这里我们将解码后的 YUV 数据转换成 RGB32 YUV420p 格式视频数据-->RGB32--> 图片显示出来
    static struct SwsContext *img_convert_ctx;
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width,pCodecCtx->height,
                                     AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    //计算RGB一帧数据大小
    auto numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,pCodecCtx->width ,pCodecCtx->height);
    //申请RGB一帧画面大小对应的空间
    uint8_t * out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    //pFrameRGB与out_buffer绑定
    avpicture_fill( (AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
                    pCodecCtx->width, pCodecCtx->height);
    //8.循环读取视频帧, 转换为 RGB 格式, 抛出信号去控件显示
    int ret, got_picture;

    //开始时间基准 和 播放时间
    //av_gettime得到的是以微秒为单位
    int64_t start_time = av_gettime();
    int64_t pts_us = 0;
    while(1)
    {
        //可以看出 av_read_frame 读取的是一帧视频，并存入一个 AVPacket 的结构中
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        //计算实际时间，比较实际时间与播放时间戳
        int64_t realTime = av_gettime() - start_time;
        while(pts_us > realTime)
        {
            msleep(5);
            realTime = av_gettime() - start_time;
        }

        //生成图片
        if (packet->stream_index == videoStream)
        {
            // 解码 packet（H264) 存在 pFrame（yuv） 里面
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
            if (ret < 0)
            {
                printf("decode error");
                return ;
            }

            //pts * av_q2d(time_base) 计算得到的单位是 秒 乘以1000000 得到微秒单位，为了与avgettime的时间比较
            pts_us = 1000000 * pFrame->pts * av_q2d(pFormatCtx->streams[videoStream]->time_base); //绝对时间

            //有解码器解码之后得到的图像数据都是 YUV420 的格式，而这里需要将其保存成图片文件
            //因此需要将得到的 YUV420 数据转换成 RGB 格式
            if (got_picture)
            {
                //YUV420转换RGB
                sws_scale(img_convert_ctx,
                          (uint8_t const * const *) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                          pFrameRGB->linesize);
                //out_buffer 与 pFrameRGB 是捆绑的，将 out_buffer 里面的数据存在 QImage 里面
                QImage tmpImg((uchar*)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                //把图像复制一份 传递给界面显示
                QImage image = tmpImg.copy();
                //显示到控件 多线程 无法控制控件 所以要发射信号
                emit SIG_GetOneImage( image );
            }
        }
        av_free_packet(packet);
        msleep(5); // 停一停
    }
    //9.回收数据
    av_free(out_buffer);
    av_free(pFrame);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}
