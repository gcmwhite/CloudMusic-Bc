#include "leftcontrolwidget.h"
#include <QPalette>
#include <QPainter>
#include <QStyleOption>

LeftControlWidget::LeftControlWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(245,245,247));
    this->setPalette(pal);
}

void LeftControlWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,226));
    p.drawLine(this->width()-1,0,this->width()-1,this->height());
}
