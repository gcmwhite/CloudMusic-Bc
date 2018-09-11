#ifndef MUSICNAMEWIDGET_H
#define MUSICNAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class MusicNameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicNameWidget(QWidget *parent = nullptr);
    void setImg(const QString &url);

private:
    void paintEvent(QPaintEvent *);

public:
    QPushButton *picBtn;
    QLabel *nameLabel;

private:
    QNetworkAccessManager *manager;
    QNetworkRequest r;

signals:

public slots:
};

#endif // MUSICNAMEWIDGET_H
