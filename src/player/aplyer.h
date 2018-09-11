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
    void play__();
    void play__(const int);
    void play__(const QString &);

private:
    QString _get_music_url_(const QString &);

private:
    int index = 0;

signals:
    void indexChanged(const int);

};

#endif // APLYER_H
