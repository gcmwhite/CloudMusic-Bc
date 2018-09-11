#include "musicplaylisttable.h"
#include <QStandardItem>
#include <QHeaderView>
#include <QDebug>

MusicPlayListTable::MusicPlayListTable(QWidget *parent)
    :QTableView(parent)
{
    this->setVisible(false);
    this->setShowGrid(false);
    this->setAlternatingRowColors(true);
    this->setFixedSize(700,500);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    head = new QStandardItemModel(this);
    QStringList list = QStringList() << "歌名" << "歌手" << "时长";
    head->setHorizontalHeaderLabels(list);
    this->setModel(head);
}

//更新播放列表
void MusicPlayListTable::changedList(const QVector<QStringList> &list)
{
    head->removeRows(0,head->rowCount());
    int size = list.size();
    for (int i = 0;i < size;i++)
    {
        head->setItem(i,0,new QStandardItem(QString(list.at(i).at(1))));
        head->setItem(i,1,new QStandardItem(QString(list.at(i).at(2))));
        head->setItem(i,2,new QStandardItem(QString(list.at(i).at(3))));
    }
    emit countChanged(head->rowCount());
}

void MusicPlayListTable::update_list(const QVector<QStringList> &list)
{
    int size = list.size();
    int row = head->rowCount();
    for (int i = 0;i < size;i++)
    {
        ++row;
        head->setItem(i,0,new QStandardItem(QString(list.at(i).at(1))));
        head->setItem(i,1,new QStandardItem(QString(list.at(i).at(2))));
        head->setItem(i,2,new QStandardItem(QString(list.at(i).at(3))));
    }
    emit countChanged(head->rowCount());
}

void MusicPlayListTable::clearList()
{
    head->removeRows(0,head->rowCount());
    emit countChanged(0);
}
