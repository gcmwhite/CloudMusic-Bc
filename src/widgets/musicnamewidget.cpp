#include "musicnamewidget.h"
#include <QHBoxLayout>
#include <QPixmap>
#include <QNetworkReply>
#include <QPainter>
#include <QDebug>

MusicNameWidget::MusicNameWidget(QWidget *parent) : QWidget(parent)
{
    this->setVisible(false);
    this->setFixedHeight(60);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    picBtn = new QPushButton;
    picBtn->setFlat(true);
    picBtn->setFixedSize(60,60);
    picBtn->setIconSize(QSize(60,60));
    nameLabel = new QLabel;
    mainLayout->addWidget(picBtn);
    mainLayout->addWidget(nameLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(10);
    mainLayout->setAlignment(Qt::AlignLeft);
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,[=](QNetworkReply *reply){
        QPixmap pix;
        pix.loadFromData(reply->readAll());
        picBtn->setIcon(QIcon(pix.scaled(60,60,Qt::KeepAspectRatio)));
        reply->deleteLater();
    });
}

void MusicNameWidget::setImg(const QString &url)
{
    qDebug() << "picUrl:" << url;
    r.setUrl(QUrl(url));
    manager->get(r);
}

void MusicNameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QColor(225,225,226));
    p.drawLine(0,0,this->width(),0);
}
