#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QVector>

class PlayList : public QObject
{
    Q_OBJECT
public:
    explicit PlayList(QObject *parent = nullptr);
    void addList(const QVector<QStringList> &);
    void updateList(const QVector<QStringList> &);
    void clearList();

public:
    static QVector<QStringList> list;
    static QVector<QStringList> update_list;
    enum updateStatus{
        ChangedList,
        UpdateList,
        ClearList
    };

signals:
    void updateList(const updateStatus);

public slots:

};

#endif // PLAYLIST_H
