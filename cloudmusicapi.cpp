#include "cloudmusicapi.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QFileInfo>
#include <QFile>
#include <QDebug>

CloudMusicAPI::CloudMusicAPI(QObject *parent) : QObject(parent)
{

}

QString CloudMusicAPI::getJson(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("Appver","1.5.2");
    req.setRawHeader("Referer","http://music.163.com/");
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = manager->get(req);
    QEventLoop loop;
    this->connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    reply->deleteLater();
    return QString(reply->readAll());
}

QString CloudMusicAPI::download(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("Appver","1.5.2");
    req.setRawHeader("Referer","http://music.163.com/");
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QFileInfo info(QUrl(url).path());
    QString fileName(info.fileName());
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "file open error";
        delete file;
        return "";
    }
    QNetworkReply *reply = manager->get(req);
    this->connect(reply,&QNetworkReply::readyRead,this,[=](){
        if (file)
        {
            file->write(reply->readAll());
        }
    });
    this->connect(reply,&QNetworkReply::finished,this,[=](){
        file->flush();
        file->close();
        reply->deleteLater();
        delete file;
    });
    QEventLoop loop;
    this->connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    return fileName;
}

QByteArray CloudMusicAPI::readImg(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("Appver","1.5.2");
    req.setRawHeader("Referer","http://music.163.com/");
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = manager->get(req);
    QEventLoop loop;
    this->connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    reply->deleteLater();
    return QByteArray(reply->readAll());
}

void CloudMusicAPI::getMusicUrl(QString id)
{
    QString url = "http://music.163.com/song/media/outer/url?id=";
    url.append(id).append(".mp3");
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("Appver","1.5.2");
    req.setRawHeader("Referer","http://music.163.com/");
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(req);
    QEventLoop loop;
    this->connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 302)
    {
        QString newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
        qDebug() << newUrl;
        emit musicUrl(newUrl);
    }
}
