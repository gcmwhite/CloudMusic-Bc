#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QLabel>
#include <QVector>

class MusicListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListWidget(QWidget *parent = nullptr);
    void playlist_detail(const QString &);

private:
    QTableView *playlist_detail_table;
    QVBoxLayout *mainLayout;
    QStandardItemModel *head;
    QLabel *listInformationLabel;
    QString listId;                         //歌单的id
    QStringList idList;                     //歌曲的id列表
    QVector<QStringList> vector_list;              //歌曲


signals:
    void addList(const int,const QString &,const QStringList &);
    void addList(const QVector<QStringList> &);

public slots:
};

#endif // MusicListWidget_H
