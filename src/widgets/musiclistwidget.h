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

public:
    QTableView *playlist_detail_table;

private:
    QVBoxLayout *mainLayout;
    QStandardItemModel *head;
    QLabel *listInformationLabel;
    QVector<QStringList> vector_list;              //歌曲


signals:
    void listChanged(const QVector<QStringList> &);

public slots:
};

#endif // MusicListWidget_H
