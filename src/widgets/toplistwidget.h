#ifndef TOPLISTWIDGET_H
#define TOPLISTWIDGET_H

#include <QWidget>
#include "gridwidget.h"

class TopListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopListWidget(const QString &,QWidget *parent = nullptr);

public:
    GridWidget *gridWidget;

signals:
//    void top_list_id(const QString &);

public slots:
};

#endif // TOPLISTWIDGET_H
