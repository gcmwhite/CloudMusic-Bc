#ifndef CURRENTMUSICPLAYLISTWIDGET_H
#define CURRENTMUSICPLAYLISTWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QLabel>

class CurrentMusicPlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CurrentMusicPlayListWidget(QWidget *parent = nullptr);
    void playlist_detail(const QString &);

private:
    QTableView *playlist_detail_table;
    QVBoxLayout *mainLayout;
    QStandardItemModel *head;
    QLabel *listInformationLabel;
    QString listId;                         //歌单的id
    QStringList idList;                     //歌曲的id列表


signals:
    void addList(const int,const QString &,const QStringList &);

public slots:
};

#endif // CURRENTMUSICPLAYLISTWIDGET_H
