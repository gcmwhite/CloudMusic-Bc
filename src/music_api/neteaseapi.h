#ifndef NETEASEAPI_H
#define NETEASEAPI_H

#include <QNetworkAccessManager>
#include <QByteArray>
#include <QNetworkRequest>
#include <QObject>
#include <QNetworkReply>

class NetEaseApi : public QObject
{
    Q_OBJECT
public:
    NetEaseApi(QObject *parent = 0);
    QString search(const QString &keywords,const int limit = 30,const int offset = 0,const int type = 1);
    void login(const QString &,const QString &);
    QString user_playlist(const QString &id);
    QString playlist_hot();
    QString top_playlist(int index = 1);
    QString music_url(const QString &);
    bool check_music(const QString &);
    QString top_list();
    QString login_status();
    QString playlist_detail(const QString &);

private:
    QString _get_(const QString &);
    bool _isDigit_(const QString &);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply *reply;
    const QString BaseUrl { "http://localhost:3000" };

};

#endif // NETEASEAPI_H
