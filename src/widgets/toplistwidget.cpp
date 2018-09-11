#include "toplistwidget.h"
//#include "imagepusubutton.h"
#include "gridwidget.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
//#include <QGridLayout>
#include <QVBoxLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

TopListWidget::TopListWidget(const QString &data, QWidget *parent)
    : QWidget(parent)
{
//    QGridLayout *mainLayout = new QGridLayout(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QVector<QStringList> vec_list;

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8(),&jsonError);
    if (!document.isNull() && jsonError.error == QJsonParseError::NoError)
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("code"))
            {
                if (object["code"].toInt() == 200)
                {
                    if (object.contains("list"))
                    {
                        QJsonArray list = object["list"].toArray();
                        int list_count = list.count();
                        vec_list.reserve(list_count);
                        for (int i = 0;i < list_count;i++)
                        {
                            QJsonValue id = list.at(i).toObject()["id"];
                            QJsonValue name = list.at(i).toObject()["name"];
                            QJsonValue coverImgUrl = list.at(i).toObject()["coverImgUrl"];
                            QJsonValue description = list.at(i).toObject()["description"];
                            QStringList list;
                            list << QString::number(id.toDouble(),'s',0) << name.toString() << coverImgUrl.toString() << description.toString();
                            vec_list.append(list);

//                            ImagePusuButton *btn = new ImagePusuButton(name.toString());
//                            btn->setToolTip(description.toString());
//                            connect(btn,&ImagePusuButton::clicked,this,[=](){
//                                QString idstr = QString::number(id.toDouble(),'s',0);
//                                emit top_list_id(idstr);
//                            });
//                            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//                            QNetworkRequest request;
//                            request.setUrl(QUrl(coverImgUrl.toString()));
//                            connect(manager,&QNetworkAccessManager::finished,this,[=](QNetworkReply *reply){
//                                QPixmap pix;
//                                pix.loadFromData(reply->readAll());
//                                btn->setImg(pix);
//                                manager->disconnect();
//                                reply->deleteLater();
//                                manager->deleteLater();
//                            });
//                            manager->get(request);
//                            mainLayout->addWidget(btn,i / 6,i % 6);
                        }
                    }
                }
            }
        }
    }
    gridWidget = new GridWidget(vec_list);
    mainLayout->addWidget(gridWidget);
}
