#include "neteaseapi.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QEventLoop>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QMessageBox>

NetEaseApi::NetEaseApi(QObject *parent)
    :QObject(parent)
{
    manager = new QNetworkAccessManager(this) ;
//    request.setRawHeader("Accept-Encoding","gzip, deflate, br");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.9");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Referer","http://music.163.com/");
    request.setRawHeader("Origin","http://music.163.com");
    request.setRawHeader("Host","music.163.com");
    request.setRawHeader("Connection","keep-alive");
    request.setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.84 Safari/537.36");

}

bool NetEaseApi::_isDigit_(const QString &str)
{
    int length = str.length();
    for (int i = 0;i < length;i++)
    {
        if (str.at(i) < '0' || str.at(i) > '9')
            return false;
    }
    return true;
}

QString NetEaseApi::_get_(const QString &url)
{
    qDebug() << "url:" << url;
    request.setUrl(QUrl(url));
    reply = manager->get(request);
    QEventLoop eventLoop;
    connect(manager,&QNetworkAccessManager::finished,&eventLoop,&QEventLoop::quit);
    eventLoop.exec();
    QString reply_data { reply->readAll() };
    return reply_data;
}

//搜索
QString NetEaseApi::search(const QString &keywords, const int limit, const int offset, const int type)
{
    QString path { "/search" };
    QString url {
        QString("%1%2?keywords=%3&limit=%4&offset=%5&type=%6").arg(BaseUrl).arg(path).arg(keywords).arg(limit).arg(offset).arg(type)
    };
    return _get_(url);
}

//登录
void NetEaseApi::login(const QString &user, const QString &password)
{
    QString url;
    if (_isDigit_(user))
    {
        url = QString("%1/login/cellphone?phone=%2&password=%3").arg(BaseUrl).arg(user).arg(password);
    } else {
        url = QString("%1/login?email=%2&password=%3").arg(BaseUrl).arg(user).arg(password);
    }
    QString reply { _get_(url) };
//    qDebug() << "reply:" << reply;
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(reply.toUtf8(),&jsonError);
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("code"))
            {
                QJsonValue value = object.value("code");
                qDebug() << "login code:" << value;
                if (value.toInt() == 200)
                {
                    qDebug() << "login successful!";
                } else {
                    qDebug() << "login failed";
                    QMessageBox::warning(nullptr,"注意","登录失败！\ncode = "+value.toString(),QMessageBox::Ok);
                }
            }
        }
    }

}

//登录状态检查
QString NetEaseApi::login_status()
{
    QString url {
        BaseUrl + "/login/status"
    };
    return _get_(url);
}

//获取用户歌单
QString NetEaseApi::user_playlist(const QString &id)
{
    QString url {
        QString("%1/user/playlist?uid=%2").arg(BaseUrl).arg(id)
    };
    return _get_(url);
}

//热门歌单分类
QString NetEaseApi::playlist_hot()
{
    QString url {
        BaseUrl + "/playlist/hot"
    };
    return _get_(url);
}

//歌单（网友精选碟）
QString NetEaseApi::top_playlist(int index)
{
//    QString url {
//        BaseUrl + "/top/playlist"
//    };
    return _get_("http://music.163.com/api/playlist/list?order=hot&limit=30&offset=" + QString::number(index));
}

//获取音乐url
QString NetEaseApi::music_url(const QString &id)
{
    QString url {
        BaseUrl + "/music/url?id=" + id
    };
    return _get_(url);
}

//检查音乐是否可用
bool NetEaseApi::check_music(const QString &id)
{
    QString url {
        BaseUrl + "/check/music?id=" + id
    };
    QString reply { _get_(url) };
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(reply.toUtf8(),&jsonError);
    if (!document.isNull() && jsonError.error == QJsonParseError::NoError)
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("success"))
            {
                QJsonValue value = object.value("success");
                qDebug() << "check_music:" << value;
                if (value.toBool())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//音乐榜单
QString NetEaseApi::top_list()
{
    return _get_("http://music.163.com/api/toplist");
}

//playlist_detail?id=
QString NetEaseApi::playlist_detail(const QString &id)
{
    return _get_("http://music.163.com/api/playlist/detail?id=" + id);
}

