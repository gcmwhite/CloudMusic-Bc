#include "statuswidget.h"
#include <QPalette>
#include <QPainter>

StatusWidget::StatusWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(43);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(246,246,248));
    this->setPalette(pal);
}

void StatusWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,226));
    p.drawLine(0,0,this->width(),0);
    p.setPen(QColor(Qt::black));
    for (int i = 0;i < 3;i++)
    {
        p.drawLine(this->width()-4,this->height()*(0.7+0.1*i),this->width()-this->height()*(0.3-i*0.1),this->height()-4);
    }
    /*
    p.drawLine(this->width()-4,this->height()*0.7,this->width()-this->height()*0.3,this->height()-4);
    p.drawLine(this->width()-4,this->height()*0.8,this->width()-this->height()*0.2,this->height()-4);
    p.drawLine(this->width()-4,this->height()*0.9,this->width()-this->height()*0.1,this->height()-4);
    */
}
