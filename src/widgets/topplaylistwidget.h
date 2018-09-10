#ifndef TOPPLAYLISTWIDGET_H
#define TOPPLAYLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class TopPlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopPlayListWidget(QWidget *parent = nullptr);
    void list(const QString &);

private:
    QVBoxLayout *mainLayout;
    QGridLayout *imgBtnLayout;

    QLabel *pageLabel_1;
    QLabel *pageLabel_2;
    QLineEdit *pageLineEdit;

    int index = 1;
    int total_page;

signals:
    void switch_page(int);
    void top_playlist_id(const QString &);

public slots:

};

#endif // TOPPLAYLISTWIDGET_H
