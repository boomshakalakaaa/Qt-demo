#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include "videoshow.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

private slots:
    void on_pb_play_clicked();

private:
    Ui::VideoPlayer *ui;
    VideoShow* m_videoShow;

};

#endif // VIDEOPLAYER_H
