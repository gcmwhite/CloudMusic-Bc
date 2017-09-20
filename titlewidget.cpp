#include "titlewidget.h"
#include <QPalette>

TitleWidget::TitleWidget(QWidget *parent) : QWidget(parent)
{
    //主界面设置
    this->setMouseTracking(true);
    this->setFixedHeight(43);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(198,47,47));
    this->setPalette(pal);
}

void TitleWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        dragPosition[0] = e->globalPos();
        dragPosition[1] = dragPosition[0] - e->pos();
    }
    e->accept();
}

void TitleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
    {
        emit moveWidgetSignal(e->globalPos() - dragPosition[0] + dragPosition[1]);
    }
    emit sendEPos(e->pos());
    e->accept();
}
