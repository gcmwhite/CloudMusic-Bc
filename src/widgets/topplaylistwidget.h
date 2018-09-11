#ifndef TOPPLAYLISTWIDGET_H
#define TOPPLAYLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "gridwidget.h"

class TopPlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopPlayListWidget(QWidget *parent = nullptr);
    void list(const QString &);

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *imgBtnLayout;
    QLabel *pageLabel_1;
    QLabel *pageLabel_2;
    QLineEdit *pageLineEdit;

public:
    GridWidget *gridWidget;

    int index = 1;
    int total_page;

signals:
    void switch_page(int);
//    void top_playlist_id(const QString &);

public slots:

};

#endif // TOPPLAYLISTWIDGET_H
