#include "topplaylistwidget.h"
//#include "imagepusubutton.h"
#include "gridwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QObjectList>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>

TopPlayListWidget::TopPlayListWidget(QWidget *parent)
    : QWidget(parent)
{
    const QSize ICONSIZE(20,20);

    mainLayout = new QVBoxLayout(this);

    QPushButton *nextBtn = new QPushButton;
    nextBtn->setIcon(QIcon(":/icons/btn_next.ico"));
    nextBtn->setIconSize(ICONSIZE);
    nextBtn->setFlat(true);

    QPushButton *previousBtn = new QPushButton;
    previousBtn->setIcon(QIcon(":/icons/btn_previous.ico"));
    previousBtn->setIconSize(ICONSIZE);
    previousBtn->setFlat(true);

    pageLabel_1 = new QLabel("第 ");
    pageLineEdit = new QLineEdit;
    pageLineEdit->setPlaceholderText(QString::number(index));
    pageLineEdit->setFixedSize(30,20);
    pageLabel_2 = new QLabel;

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(previousBtn);
    btnLayout->addWidget(pageLabel_1);
    btnLayout->addWidget(pageLineEdit);
    btnLayout->addWidget(pageLabel_2);
    btnLayout->addWidget(nextBtn);
    btnLayout->addStretch();

    imgBtnLayout = new QVBoxLayout;
    imgBtnLayout->setMargin(0);
    imgBtnLayout->setSpacing(0);
    mainLayout->addLayout(imgBtnLayout);
    mainLayout->addLayout(btnLayout);
//    mainLayout->setAlignment(Qt::AlignBottom);

    //上一页
    connect(previousBtn,&QPushButton::clicked,this,[=](){
        if (index <= 1)
        {
            QMessageBox::warning(this,"注意","已经是第一页！",QMessageBox::Ok);
            return ;
        }
        emit switch_page(--index);
        pageLineEdit->setPlaceholderText(QString::number(index));
    });

    //下一页
    connect(nextBtn,&QPushButton::clicked,this,[=](){
        if (index >= total_page)
        {
            QMessageBox::warning(this,"注意","已经是最后一页！",QMessageBox::Ok);
            return ;
        }
        emit switch_page(++index);
        pageLineEdit->setPlaceholderText(QString::number(index));
    });

    //切换页数
    connect(pageLineEdit,&QLineEdit::returnPressed,this,[=](){
        int page = pageLineEdit->text().toInt();
        if (page > 0 && page <= total_page)
        {
            if (page != index)
            {
                index = page;
                emit switch_page(index);
                pageLineEdit->clear();
                pageLineEdit->setPlaceholderText(QString::number(index));
            }
        }else
        {
            QMessageBox::warning(this,tr("注意"),tr("填写数字在1到%1之间！").arg(total_page),QMessageBox::Ok);
        }
    });

}

void TopPlayListWidget::list(const QString &json)
{
    QVector<QStringList> vec_list;
    //删除控件
    while (imgBtnLayout->count())
    {
        QWidget *p = imgBtnLayout->itemAt(0)->widget();
        p->setParent(nullptr);
        imgBtnLayout->removeWidget(p);
        delete p;
    }

    //更新控件
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    if (!document.isEmpty() && jsonError.error == QJsonParseError::NoError)
    {
        if (document.isObject())
        {
            QJsonObject object = document.object();
            if (object.contains("code") && object["code"].toInt() == 200)
            {
                int total = object["total"].toInt();
                QJsonArray playlists = object["playlists"].toArray();
                int size = playlists.size();
                total_page = total / size;
                if (total % size != 0)
                {
                    total_page += 1;
                }
                pageLabel_2->setText(tr("页,共 %1 页").arg(total_page));
                vec_list.reserve(size);
                for (int i = 0;i < size;i++)
                {
                    QJsonObject object = playlists.at(i).toObject();
                    QJsonValue name = object["name"];
                    QJsonValue id = object["id"];
                    QJsonValue coverImgUrl = object["coverImgUrl"];
                    QJsonValue description = object["description"];

                    QStringList list;
                    list << QString::number(id.toDouble(),'s',0) << name.toString() << coverImgUrl.toString() << description.toString();
                    vec_list.append(list);
//                    ImagePusuButton *btn = new ImagePusuButton(name.toString());
//                    btn->setToolTip(description.toString());
//                    connect(btn,&ImagePusuButton::clicked,this,[=](){
//                        QString idstr = QString::number(id.toDouble(),'s',0);
//                        emit top_playlist_id(idstr);
//                    });
//                    imgBtnLayout->addWidget(btn,i/6,i%6);

//                    QNetworkAccessManager *manaer = new QNetworkAccessManager(this);
//                    QNetworkRequest request(QUrl(coverImgUrl.toString()));
//                    connect(manaer,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
//                        QPixmap pix;
//                        pix.loadFromData(reply->readAll());
//                        btn->setImg(pix);
//                        manaer->disconnect();
//                        reply->deleteLater();
//                        manaer->deleteLater();
//                    });
//                    manaer->get(request);
                }
            }
        }
    }
    gridWidget = new GridWidget(vec_list);
    imgBtnLayout->addWidget(gridWidget);
}

