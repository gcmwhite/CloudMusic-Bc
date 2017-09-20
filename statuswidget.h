#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // STATUSWIDGET_H
