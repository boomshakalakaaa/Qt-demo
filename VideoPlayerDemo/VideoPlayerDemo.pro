#-------------------------------------------------
#
# Project created by QtCreator 2021-04-03T12:27:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayerDemo
TEMPLATE = app

INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include\


LIBS += $$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
 $$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
 $$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
 $$PWD/ffmpeg-4.2.2/lib/avformat.lib\
 $$PWD/ffmpeg-4.2.2/lib/avutil.lib\
 $$PWD/ffmpeg-4.2.2/lib/postproc.lib\
 $$PWD/ffmpeg-4.2.2/lib/swresample.lib\
 $$PWD/ffmpeg-4.2.2/lib/swscale.lib



SOURCES += main.cpp\
        videoplayer.cpp \
    videoshow.cpp \
    videoitem.cpp

HEADERS  += videoplayer.h \
    videoshow.h \
    videoitem.h

FORMS    += videoplayer.ui \
    videoitem.ui
