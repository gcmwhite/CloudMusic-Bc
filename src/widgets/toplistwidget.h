#ifndef TOPLISTWIDGET_H
#define TOPLISTWIDGET_H

#include <QWidget>

class TopListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopListWidget(const QString &,QWidget *parent = nullptr);


signals:
    void top_list_id(const QString &);

public slots:
};

#endif // TOPLISTWIDGET_H
