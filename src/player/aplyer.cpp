#include "aplyer.h"
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QMessageBox>

APlyer::APlyer(QObject *parent)
    : QMediaPlayer(parent)
{
    //播放结束自动切换歌曲
    connect(this,&APlyer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
        qDebug() << "status:" << this->mediaStatus();
        if (status == QMediaPlayer::EndOfMedia)
        {
            next__();
        }
    });

    connect(this,&APlyer::currentMediaChanged,this,[=](){
        emit indexChanged(index);
    });
}

//上一曲
void APlyer::previous__()
{
    if (index >= 1)
    {
        play__(QString(playList.at(--index)));
    }
}

//下一曲
void APlyer::next__()
{
    if (index < playList.size() - 1)
    {
        play__(QString(playList.at(++index)));
    }
}

//播放、暂停
void APlyer::play__()
{
    if (this->state() == QMediaPlayer::PlayingState)
    {
        this->pause();
    } else {
        this->play();
    }
}

void APlyer::play__(const int n)
{
    index = n;
    play__(QString(playList.at(index)));
}

void APlyer::play__(const QString &id)
{
    QString url = _get_music_url_(id);
    if (url.isEmpty())
    {
//        QMessageBox::warning(this,"注意","获取MP3地址失败，正在尝试播放下一曲！",QMessageBox::Ok);
        qDebug() << "获取MP3地址失败，正在尝试播放下一曲！";
        next__();
    }
    this->setMedia(QMediaContent(QUrl(url)));
    this->play();
    qDebug() << "play:" << url;
}

void APlyer::play__(const QStringList &list)
{
    play__(QString(list.at(index)));
}

//添加到播放列表
void APlyer::addPlayList__(const int currentIndex, const QString &id, const QStringList &list)
{
    qDebug() << "index:" << currentIndex << "listId:" << id << "idList:" << list;
    if (listId != id)
    {
        listId.clear();
        listId = id;
        playList.clear();
        playList = list;
    }
    index = currentIndex;
    play__(playList);
}

void APlyer::addPlayList__(const QString &id)
{
    playList.append(id);
}

void APlyer::addPlayList__(const QStringList &list)
{
    playList = playList + list;
}

//获取音乐播放地址
QString APlyer::_get_music_url_(const QString &id)
{
    QString url = QString("http://music.163.com/song/media/outer/url?id=%1.mp3").arg(id);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.9");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Referer","http://music.163.com/");
    request.setRawHeader("Origin","http://music.163.com");
    request.setRawHeader("Host","music.163.com");
    request.setRawHeader("Connection","keep-alive");
    request.setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    this->connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 302)
    {
        QString newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
        manager->deleteLater();
        reply->deleteLater();
        return newUrl;
    }
    return "";
}
