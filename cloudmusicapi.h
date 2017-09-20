#ifndef CLOUDMUSICAPI_H
#define CLOUDMUSICAPI_H

#include <QObject>

class CloudMusicAPI : public QObject
{
    Q_OBJECT
public:
    explicit CloudMusicAPI(QObject *parent = nullptr);
    QString getJson(QString);
    QString download(QString);
    QByteArray readImg(QString);



signals:
    void musicUrl(QString);
    void sendJson(QString);

public slots:
    void getMusicUrl(QString);


};

#endif // CLOUDMUSICAPI_H
