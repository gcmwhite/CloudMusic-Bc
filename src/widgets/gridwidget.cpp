#include "gridwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QBitmap>
#include <QPainter>

GridWidget::GridWidget(const QVector<QStringList> &vec_list,QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);
    int size = vec_list.size();
    QNetworkRequest r;
    r.setRawHeader("Accept-Language","zh-CN,zh;q=0.9");
//        r.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
//        r.setRawHeader("Referer","http://music.163.com/");
//        r.setRawHeader("Origin","http://music.163.com");
    r.setRawHeader("Host"," p1.music.126.net");
    r.setRawHeader("Connection","keep-alive");
    r.setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
    for(int i = 0;i < size;i++)
    {
        QStringList list = vec_list.at(i);
        QString name = list.at(1);
        QString url = list.at(2);
        QLabel *imgLable = new QLabel;
        imgLable->setAlignment(Qt::AlignCenter);
        QLabel *textLabel = new QLabel;
        textLabel->setAlignment(Qt::AlignCenter);
        if (name.size() >= 11)
        {
            name.insert(10,'\n');
        }
        textLabel->setText(name);
        QPushButton *imgBtn = new QPushButton;
        imgBtn->setFlat(true);
        imgBtn->setMinimumSize(90,110);
        imgBtn->setToolTip(list.at(3));
        QVBoxLayout *btn_layout = new QVBoxLayout(imgBtn);
        btn_layout->setMargin(0);
        btn_layout->setSpacing(0);
        btn_layout->addWidget(imgLable);
        btn_layout->addWidget(textLabel);
        r.setUrl(QUrl(url));
        QNetworkAccessManager *m = new QNetworkAccessManager(this);
        connect(m,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
            QPixmap pix;
            pix.loadFromData(reply->readAll());
            pix = pix.scaled(750,750,Qt::KeepAspectRatio);
            pix = pixmapToRound(pix,pix.width()/22);
            imgLable->setPixmap(pix);
            reply->deleteLater();
        });
        m->get(r);
        mainLayout->addWidget(imgBtn,i/6,i%6);

        connect(imgBtn,&QPushButton::clicked,this,[=](){
            emit top_list_id(list.at(0));
        });
    }
}


//剪切图片为圆形
QPixmap GridWidget::pixmapToRound(const QPixmap &pix, int radius)
{
    if (pix.isNull())
        return QPixmap();
    QSize size(2*radius,2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0,0,size.width(),size.height(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(0,0,size.width(),size.height(),99,99);
    painter.end();
    QPixmap image = pix.scaled(size);
    image.setMask(mask);
    return image;
}
