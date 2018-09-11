#include "musiclistwidget.h"
#include "../player/playlist.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDebug>

MusicListWidget::MusicListWidget(QWidget *parent) : QWidget(parent)
{
    listInformationLabel = new QLabel;
    listInformationLabel->setAlignment(Qt::AlignLeft);
    mainLayout = new QVBoxLayout(this);
    playlist_detail_table = new QTableView;
    mainLayout->addWidget(listInformationLabel);
    mainLayout->addWidget(playlist_detail_table);
    playlist_detail_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlist_detail_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    head = new QStandardItemModel;
    playlist_detail_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headerList;
    headerList << "歌名" << "歌手" << "时长";
    head->setHorizontalHeaderLabels(headerList);
    playlist_detail_table->setModel(head);

    //添加播放表
    connect(playlist_detail_table,&QTableView::doubleClicked,this,[=](){
        emit listChanged(vector_list);
        vector_list.clear();
    });
}

void MusicListWidget::playlist_detail(const QString &json)
{
    head->removeRows(0,head->rowCount());
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    if (!document.isNull() && jsonError.error == QJsonParseError::NoError)
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("code"))
            {
                if (object["code"].toInt() == 200)
                {                    
//                    QString listId = QString::number(object["result"].toObject()["id"].toDouble(),'s',0);
                    QJsonArray tracks = object["result"].toObject()["tracks"].toArray();
                    int tracks_size = tracks.size();
                    listInformationLabel->setText(tr("<font size='5'>%1</font>&nbsp;共%2首音乐").arg(object["result"].toObject()["name"].toString()).arg(tracks_size));
                    vector_list.reserve(tracks_size);
                    for (int i = 0;i < tracks_size;i++)
                    {
                        QJsonValue id = tracks.at(i).toObject()["id"];
                        QString idList = QString::number(id.toDouble(),'s',0);
                        QString name = tracks.at(i).toObject()["name"].toString();
                        int duration = tracks.at(i).toObject()["duration"].toInt()/1000;
                        QJsonArray artists = tracks.at(i).toObject()["artists"].toArray();
                        QString artists_name;
                        for (int i = 0;i < artists.size();i++)
                        {
                            artists_name.append(artists.at(i).toObject()["name"].toString());
                            if (i == artists.size() - 1)
                                break;
                            artists_name.append("/");
                        }
                        QString picUrl = tracks.at(i).toObject()["album"].toObject()["artist"].toObject()["picUrl"].toString();
                        QString time = QString("%1分:%2秒").arg(duration/60).arg(duration%60);
                        head->setItem(i,0,new QStandardItem(name));
                        head->setItem(i,1,new QStandardItem(artists_name));
                        head->setItem(i,2,new QStandardItem(time));
                        QStringList _list;
                        _list << idList << name << artists_name << time << picUrl;;
                        vector_list.append(_list);
                    }
                }
            }
        }
    }
}
