#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QPixmap>

class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(const QVector<QStringList> &,QWidget *parent = nullptr);
    QPixmap pixmapToRound(const QPixmap &, int );

private:
    QGridLayout *mainLayout;


signals:
    void top_list_id(const QString &);

public slots:
};

#endif // GRIDWIDGET_H
