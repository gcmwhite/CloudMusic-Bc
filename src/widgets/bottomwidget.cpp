#include "bottomwidget.h"
#include <QPalette>
#include <QPainter>
#include <QDebug>

BottomWidget::BottomWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

BottomWidget::~BottomWidget()
{

}

void BottomWidget::initUI()
{
    this->setFixedHeight(43);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(246,246,248));
    this->setMouseTracking(true);
    this->setPalette(pal);

    musicPlayerBtn = new QPushButton(QIcon(":/icons/music.ico"),"");
    musicPlayerBtn->setFlat(true);
    musicPlayerBtn->setIconSize(QSize(20,20));
    connect(musicPlayerBtn,&QPushButton::clicked,[=](){
        emit musicPlayerBtn_clicked(1);         //播放界面 :1
    });
    previousBtn = new QPushButton(QIcon(":/icons/player_previous.ico"),"");
    previousBtn->setFlat(true);
    previousBtn->setIconSize(QSize(20,20));
    playBtn = new QPushButton(QIcon(":/icons/player_play.ico"),"");
    playBtn->setFlat(true);
    playBtn->setIconSize(QSize(20,20));
    nextBtn = new QPushButton(QIcon(":/icons/player_next.ico"),"");
    nextBtn->setFlat(true);
    nextBtn->setIconSize(QSize(20,20));
    muteBtn = new QPushButton(QIcon(":/icons/sound_on.ico"),"");
    muteBtn->setFlat(true);
    muteBtn->setIconSize(QSize(20,20));
    lyricBtn = new QPushButton(tr("词"));
    lyricBtn->setFixedSize(20,20);
    playlistBtn = new QPushButton;
    playlistBtn->setIcon(QIcon(":/icons/playlist.ico"));
    playlistBtn->setFixedSize(40,20);
//    playlistBtn->setFlat(true);
    playlistBtn->setText(" 0");
    currentTimeLable = new QLabel("00:00");
    remainingTimeLable = new QLabel("00:00");
    timeSlider = new QSlider(Qt::Horizontal);
    timeSlider->setStyleSheet("\
                              QSlider::groove:horizontal {\
                                  height: 4px;\
                                  background:transparent;\
                              }\
                              QSlider::handle:horizontal {\
                                  border: none;\
                                  border-image:url(:/icons/point.ico);\
                                  width: 14px;\
                                  margin:-5px 0px -5px 0px;\
                              }\
                              QSlider::add-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(194,194,196);\
                              }\
                              QSlider::sub-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(232,60,60);\
                              }\
                              ");
    soundSlider = new QSlider(Qt::Horizontal);
    soundSlider->setRange(0,100);
    soundSlider->setValue(100);
    soundSlider->setFixedWidth(90);
    soundSlider->setStyleSheet("\
                              QSlider::groove:horizontal {\
                                  height: 4px;\
                                  background:transparent;\
                              }\
                              QSlider::handle:horizontal {\
                                  border-image: url(:/icons/dot_red.ico);\
                                  border: none;\
                                  width: 8px;\
                                  margin:-2px 0px -2px 0px;\
                              }\
                              QSlider::add-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(194,194,196);\
                              }\
                              QSlider::sub-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(232,60,60);\
                              }\
                              ");

    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(musicPlayerBtn);
    mainLayout->addWidget(previousBtn);
    mainLayout->addWidget(playBtn);
    mainLayout->addWidget(nextBtn);
    mainLayout->addWidget(currentTimeLable);
    mainLayout->addWidget(timeSlider);
    mainLayout->addWidget(remainingTimeLable);
    mainLayout->addWidget(muteBtn);
    mainLayout->addWidget(soundSlider);
    mainLayout->addWidget(lyricBtn);
    mainLayout->addWidget(playlistBtn);

}

void BottomWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,226));
    p.drawLine(0,0,this->width(),0);
    p.setPen(QColor(Qt::black));
    for (int i = 0;i < 3;i++)
    {
        p.drawLine(this->width()-4,this->height()*(0.7+0.1*i),this->width()-this->height()*(0.3-i*0.1),this->height()-4);
    }
}

/*
void BottomWidget::mousePressEvent(QMouseEvent *e)
{

    mainWidgetPtr = (QWidget *)this->parent();
    if (e->button() == Qt::LeftButton)
    {
        mousePoint = e->globalPos();
        originGeometry = mainWidgetPtr->geometry();
        pressMouseFlag = true;
        e->accept();
    }

    return QWidget::mousePressEvent(e);
}

void BottomWidget::mouseReleaseEvent(QMouseEvent *e)
{

    qDebug() << "退出！";
    pressMouseFlag = false;
    mainWidgetPtr = nullptr;

    return QWidget::mouseReleaseEvent(e);
}

void BottomWidget::mouseMoveEvent(QMouseEvent *e)
{

    if (this->width() - e->pos().x() <= 10 && this->height() - e->pos().y() <= 10)
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if (pressMouseFlag)
        {
            qDebug() << "进入";
            int dx { e->globalPos().x() - mousePoint.x() };
            int dy { e->globalPos().y() - mousePoint.y() };
            QRect rc { originGeometry };
            rc.setRight(rc.right() + dx);
            rc.setBottom(rc.bottom() + dy);
            mainWidgetPtr->setGeometry(rc);
            update();
        }
    } else
        this->setCursor(Qt::ArrowCursor);

    return QWidget::mouseMoveEvent(e);
}
*/
