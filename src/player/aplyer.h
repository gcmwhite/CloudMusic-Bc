#ifndef APLYER_H
#define APLYER_H

#include <QMediaPlayer>

class APlyer : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit APlyer(QObject *parent = nullptr);
    void next__();
    void previous__();
    void addPlayList__(const int,const QString &,const QStringList&);
    void addPlayList__(const QString &);
    void addPlayList__(const QStringList &);
    void play__();
    void play__(const QString &);
    void play__(const QStringList &);

private:
    QString _get_music_url_(const QString &);

private:
    QStringList playList;
    QString listId;
    int index = 0;

signals:

public slots:
};

#endif // APLYER_H
