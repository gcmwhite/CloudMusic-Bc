#include "currentmusicplaylistwidget.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDebug>

CurrentMusicPlayListWidget::CurrentMusicPlayListWidget(QWidget *parent) : QWidget(parent)
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
        int index = playlist_detail_table->currentIndex().row();
//        qDebug() << "index:" << index << "listId:" << listId << "idList:" << idList;
        emit addList(index,listId,idList);
    });
}

void CurrentMusicPlayListWidget::playlist_detail(const QString &json)
{
    listId.clear();
    idList.clear();
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
                    listId = QString::number(object["result"].toObject()["id"].toDouble(),'s',0);
                    QJsonArray tracks = object["result"].toObject()["tracks"].toArray();
                    int tracks_size = tracks.size();
                    listInformationLabel->setText(tr("<font size='5'>%1</font>&nbsp;共%2首音乐").arg(object["result"].toObject()["name"].toString()).arg(tracks_size));
                    for (int i = 0;i < tracks_size;i++)
                    {
                        QJsonValue id = tracks.at(i).toObject()["id"];
                        idList << QString::number(id.toDouble(),'s',0);
                        QJsonValue name = tracks.at(i).toObject()["name"];
                        QJsonValue duration = tracks.at(i).toObject()["duration"];
                        QJsonArray artists = tracks.at(i).toObject()["artists"].toArray();
                        QString artists_name;
                        for (int i = 0;i < artists.size();i++)
                        {
                            artists_name.append(artists.at(i).toObject()["name"].toString());
                            if (i == artists.size() - 1)
                                break;
                            artists_name.append("/");
                        }
                        head->setItem(i,0,new QStandardItem(name.toString()));
                        head->setItem(i,1,new QStandardItem(artists_name));
                        int duration_time = duration.toInt()/1000;
                        head->setItem(i,2,new QStandardItem(QString("%1分:%2秒").arg(duration_time/60).arg(duration_time%60)));

                    }
                }
            }
        }
    }
}
