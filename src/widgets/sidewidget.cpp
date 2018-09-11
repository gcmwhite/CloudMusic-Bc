#include "sidewidget.h"
#include <QPalette>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

SideWidget::SideWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

SideWidget::~SideWidget()
{

}

void SideWidget::initUI()
{
    this->setFixedWidth(230);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(245,245,247));
    this->setPalette(pal);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);

    QLabel *recommendLabel = new QLabel("推荐");
    QPushButton *topListBtn = new QPushButton("榜单");
    QPushButton *topPlayListBtn = new QPushButton("歌单");
    QPushButton *djRadioBtn = new QPushButton("主播电台");
    QPushButton *albumBtn = new QPushButton("新碟上架");
    QLabel *myMusicLabel = new QLabel("我的音乐");
//    QPushButton *currentMusicPlayListBtn = new QPushButton("播放列表");

    addWidget(recommendLabel);
//    addWidget(currentMusicPlayListBtn);     //:1
    addWidget(topListBtn);                  //:2
    addWidget(topPlayListBtn);              //:3
    addWidget(djRadioBtn);                  //:4
    addWidget(albumBtn);                    //:5
    addWidget(myMusicLabel);

}

void SideWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,226));
    p.drawLine(this->width()-1,0,this->width()-1,this->height());
}

void SideWidget::on_btn_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    emit btn_clicked(btn->objectName().toInt());
}

//添加控件
void SideWidget::addWidget(QWidget *w)
{
    QString btnCss = "QPushButton {"
                         "height: 22px;"
                         "border: 2px solid rgb(194,194,196);"
                         "border-radius:11px;"
                         "background-color: rgb(225,225,225);"
                         "}"
                         "QPushButton:hover {"
                         "background-color: rgb(240,240,240);"
                         "}"
                         "QPushButton:pressed {"
                         "background-color: rgb(210,210,210)"
                        "}";
    static int count = 2;
    QPushButton *btn = dynamic_cast<QPushButton *>(w);
    if (btn)
    {
        btn->setObjectName(QString::number(count++));
        btn->setStyleSheet(btnCss);
        connect(btn,&QPushButton::clicked,this,&SideWidget::on_btn_clicked);
    }
    mainLayout->addWidget(w);
}
