/********************************************************************************
** Form generated from reading UI file 'videoplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYER_H
#define UI_VIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <videoitem.h>

QT_BEGIN_NAMESPACE

class Ui_VideoPlayer
{
public:
    QVBoxLayout *verticalLayout;
    VideoItem *wdg_show;
    QWidget *wdg_ctrl;
    QPushButton *pb_play;

    void setupUi(QWidget *VideoPlayer)
    {
        if (VideoPlayer->objectName().isEmpty())
            VideoPlayer->setObjectName(QStringLiteral("VideoPlayer"));
        VideoPlayer->resize(800, 600);
        VideoPlayer->setMinimumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(VideoPlayer);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wdg_show = new VideoItem(VideoPlayer);
        wdg_show->setObjectName(QStringLiteral("wdg_show"));
        wdg_show->setMinimumSize(QSize(800, 560));

        verticalLayout->addWidget(wdg_show);

        wdg_ctrl = new QWidget(VideoPlayer);
        wdg_ctrl->setObjectName(QStringLiteral("wdg_ctrl"));
        wdg_ctrl->setMinimumSize(QSize(800, 40));
        wdg_ctrl->setMaximumSize(QSize(16777215, 40));
        pb_play = new QPushButton(wdg_ctrl);
        pb_play->setObjectName(QStringLiteral("pb_play"));
        pb_play->setGeometry(QRect(20, 0, 100, 30));

        verticalLayout->addWidget(wdg_ctrl);


        retranslateUi(VideoPlayer);

        QMetaObject::connectSlotsByName(VideoPlayer);
    } // setupUi

    void retranslateUi(QWidget *VideoPlayer)
    {
        VideoPlayer->setWindowTitle(QApplication::translate("VideoPlayer", "VideoPlayer", 0));
        pb_play->setText(QApplication::translate("VideoPlayer", "Play", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoPlayer: public Ui_VideoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYER_H
