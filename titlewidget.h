#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    QPoint dragPosition[2];         //移动量

signals:
    void moveWidgetSignal(QPoint);
    void sendEPos(QPoint);

public slots:
};

#endif // TITLEWIDGET_H
