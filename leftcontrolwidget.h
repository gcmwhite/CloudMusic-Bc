#ifndef LEFTCONTROLWIDGET_H
#define LEFTCONTROLWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class LeftControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftControlWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // LEFTCONTROLWIDGET_H
