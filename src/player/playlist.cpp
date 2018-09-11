#include "playlist.h"

PlayList::PlayList(QObject *parent) : QObject(parent)
{

}

//添加到播放列表
void PlayList::addList(const QVector<QStringList> &temp)
{
    list.clear();
    list = temp;
    emit updateList(updateStatus::ChangedList);
}

void PlayList::updateList(const QVector<QStringList> &temp)
{
    update_list = temp;
    list = list + update_list;
    emit updateList(updateStatus::UpdateList);
}

//清空列表
void PlayList::clearList()
{
    list.clear();
    emit updateList(updateStatus::ClearList);
}
