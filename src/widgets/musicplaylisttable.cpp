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
void MusicPlayListTable::update_list(const QVector<QStringList> &list)
{
    head->removeRows(0,head->rowCount());
    int size = list.size();
    for (int i = 0;i < size;i++)
    {
        QStringList temp = list.at(i);
        head->setItem(i,0,new QStandardItem(QString(temp.at(0))));
        head->setItem(i,1,new QStandardItem(QString(temp.at(1))));
        head->setItem(i,2,new QStandardItem(QString(temp.at(2))));
    }
    emit countChanged(head->rowCount());
}

void MusicPlayListTable::update_list(const QStringList &list)
{
    int row = head->rowCount() + 1;
    head->setItem(row,0,new QStandardItem(QString(list.at(0))));
    head->setItem(row,1,new QStandardItem(QString(list.at(1))));
    head->setItem(row,2,new QStandardItem(QString(list.at(2))));
    emit countChanged(head->rowCount());
}
