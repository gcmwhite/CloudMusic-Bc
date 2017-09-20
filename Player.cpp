#include "Player.h"
#include "dat.h"
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QTextBrowser>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QHashIterator>
#include <QHeaderView>
#include <QDebug>

QHash<int,QStringList> Dat::idPlayListHash;
QHash<QString,QStringList> Dat::idListHash;
int Dat::currentId = 0;

Player::Player(QWidget *parent)
    : QWidget(parent)
{
    playerInit();       //播放器初始化
}

Player::~Player()
{

}

void Player::playerInit()       //播放器初始化
{
    playListWidget = new QWidget;
    createApi();            //API
    createMainWidget();     //创建主界面
    createLeftControlWidget();      //创建左控栏
    createTitleWidget();            //创建标题栏
    createStatusWidget();           //创建状态栏
    creatwCenterWidget();           //中央布局



    musicPlayer = new QMediaPlayer(this);
    playerConnect();        //播放器逻辑槽
}

void Player::createMainWidget()         //创建主界面
{
    this->resize(930,510);
    this->setWindowFlags(Qt::FramelessWindowHint);

    mainLayout = new QVBoxLayout(this);
    leftControlScrollArea = new QScrollArea;
    leftControlScrollArea->setFrameShape(QFrame::NoFrame);
    leftControlScrollArea->setFixedWidth(190);
    leftControlScrollArea->setWidgetResizable(true);
    centerSCrollArea = new QScrollArea;
    centerSCrollArea->setFrameShape(QFrame::NoFrame);
    centerSCrollArea->setWidgetResizable(true);
    titleWidget = new TitleWidget;
    statusWidget = new StatusWidget;
    mainLayout->addWidget(titleWidget,1);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(leftControlScrollArea);
    hBoxLayout->addWidget(centerSCrollArea);
    hBoxLayout->setMargin(0);
    mainLayout->addLayout(hBoxLayout,9);
    mainLayout->addWidget(statusWidget,1);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
}

void Player::createLeftControlWidget()          //创建左控栏
{
    leftControlWidget = new LeftControlWidget;
    QString btnCss = "QPushButton {"
                         "height: 22px;"
                         "border: 2px solid rgb(194,194,196);"
                         "border-radius:11px;"
                         "background-color: rgb(225,225,225);"
                         "}"
                         "QPushButton:hover {"
                         "background-color: rgb(240,240,240);"
                         "}"
                         "QPushButton:pressed {"
                         "background-color: rgb(210,210,210)"
                         "}";
    recommendLabel = new QLabel(tr("推荐"));
    topListBtn = new QPushButton(tr("音乐榜单"));
    topListBtn->setStyleSheet(btnCss);
    topListBtn->setObjectName("0");
    playListBtn = new QPushButton(tr("歌单"));
    playListBtn->setStyleSheet(btnCss);
    playListBtn->setObjectName("1");
    djRadioBtn = new QPushButton(tr("主播电台"));
    djRadioBtn->setStyleSheet(btnCss);
    djRadioBtn->setObjectName("2");
    albumBtn = new QPushButton(tr("新碟上架"));
    albumBtn->setStyleSheet(btnCss);
    albumBtn->setObjectName("3");
    QVBoxLayout *vBoxLayout = new QVBoxLayout(leftControlWidget);
    vBoxLayout->addWidget(recommendLabel);
    vBoxLayout->addWidget(topListBtn);
    vBoxLayout->addWidget(playListBtn);
    vBoxLayout->addWidget(djRadioBtn);
    vBoxLayout->addWidget(albumBtn);
    vBoxLayout->addStretch(10);
    leftControlScrollArea->setWidget(leftControlWidget);
}

void Player::creatwCenterWidget()               //创建中央布局
{
    createTopListWidget();
    createplayListWidget(0);
    createdjRadioWidget();
    createAlbumWidget();
    createMusicPlayWidget();

    stackWidget = new QStackedWidget;
    stackWidget->addWidget(topListWidget);
    stackWidget->addWidget(playListWidget);
    stackWidget->addWidget(djRadioWidget);
    stackWidget->addWidget(albumWidget);
    stackWidget->addWidget(musicPlayWidget);
    musicTableWidget = new QWidget;
    stackWidget->addWidget(musicTableWidget);

    centerSCrollArea->setWidget(stackWidget);

    this->connect(topListBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(topListWidget);
        qDebug() << 1;
    });
    this->connect(playListBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(playListWidget);
        qDebug() << 2;
    });
    this->connect(djRadioBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(djRadioWidget);
        qDebug() << 3;
    });
    this->connect(albumBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(albumWidget);
        qDebug() << 4;
    });
    this->connect(musicPlayerBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(musicPlayWidget);
        qDebug() << 5;
    });
    this->connect(titleBtn,&QPushButton::clicked,stackWidget,[=](){
        stackWidget->setCurrentWidget(topListWidget);
        qDebug() << 1;
    });

}

void Player::createTitleWidget()                //创建标题栏
{
    windowCloseBtn = new QPushButton(QIcon(":/window_close.ico"),"");
    windowCloseBtn->setIconSize(QSize(20,20));
    windowCloseBtn->setFlat(true);
    windowCloseBtn->setToolTip(tr("关闭窗口"));
    this->connect(windowCloseBtn,&QPushButton::clicked,this,[=](){
        this->close();
    });
    windowMaxSizeBtn = new QPushButton(QIcon(":/window_max_size.ico"),"");
    windowMaxSizeBtn->setIconSize(QSize(20,20));
    windowMaxSizeBtn->setFlat(true);
    windowMaxSizeBtn->setToolTip(tr("最大化窗口"));
    this->connect(windowMaxSizeBtn,&QPushButton::clicked,this,[=](){
        if (this->isMaximized())
        {
            this->showNormal();
            windowMaxSizeBtn->setIcon(QIcon(":/window_max_size.ico"));
        } else {
            this->showMaximized();
            windowMaxSizeBtn->setIcon(QIcon(":/window-restore.ico"));
        }
    });
    windowMinSizeBtn = new QPushButton(QIcon(":/window_min_size.ico"),"");
    windowMinSizeBtn->setIconSize(QSize(20,20));
    windowMinSizeBtn->setFlat(true);
    windowMinSizeBtn->setToolTip(tr("最小化窗口"));
    this->connect(windowMinSizeBtn,&QPushButton::clicked,this,[=](){
        this->showMinimized();
    });
    titleBtn = new QPushButton(QIcon(":/cloud_music_logo.ico"),
                               tr("CloudMusic of BC"));
    titleBtn->setIconSize(QSize(36,36));
    titleBtn->setFlat(true);
#ifdef Q_OS_LINUX
    QFontDatabase::addApplicationFont(":/fonts/华文隶书.ttf");
    titleBtn->setStyleSheet("QPushButton {font-family:STLiti;font-size:16pt;}"
                            "QPushButton:pressed {background-color:rgb(198,47,47);}");
#endif
    searchBtn = new QPushButton;
    searchBtn->setFixedSize(215,20);
    searchBtn->setIcon(QIcon(":/search.ico"));
    searchBtn->setIconSize(QSize(15,15));
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setFlat(true);
    searchBtn->setStyleSheet("background-color:rgb(168,40,40);border-radius:10px;"
                             "text-align:right;padding-right:10px;");
    searchLineEdit = new QLineEdit(searchBtn);
    searchLineEdit->setPlaceholderText(tr("搜索音乐，歌手，歌词，用户"));
    searchLineEdit->setFixedSize(190,20);
    searchLineEdit->setStyleSheet("background-color:rgb(168,40,40);color:rgb(199,115,115);"
                                   "border-top-left-radius:10px;border-bottom-left-radius:10px;");
    QHBoxLayout *hBoxLayout = new QHBoxLayout(titleWidget);
    hBoxLayout->setMargin(0);
    hBoxLayout->addWidget(titleBtn);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(searchBtn);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(windowMinSizeBtn);
    hBoxLayout->addWidget(windowMaxSizeBtn);
    hBoxLayout->addWidget(windowCloseBtn);

    //窗口移动信号
    this->connect(titleWidget,&TitleWidget::moveWidgetSignal,this,[=](QPoint movePos){
        this->move(movePos);
    });
}

void Player::createStatusWidget()               //创建状态栏
{
    musicPlayerBtn = new QPushButton(QIcon(":/music.ico"),"");
    musicPlayerBtn->setFlat(true);
    musicPlayerBtn->setIconSize(QSize(20,20));
    previousBtn = new QPushButton(QIcon(":/player_previous.ico"),"");
    previousBtn->setFlat(true);
    previousBtn->setIconSize(QSize(20,20));
    pauseBtn = new QPushButton(QIcon(":/player_play.ico"),"");
    pauseBtn->setFlat(true);
    pauseBtn->setIconSize(QSize(20,20));
    nextBtn = new QPushButton(QIcon(":/player_next.ico"),"");
    nextBtn->setFlat(true);
    nextBtn->setIconSize(QSize(20,20));
    muteBtn = new QPushButton(QIcon(":/sound_on.ico"),"");
    muteBtn->setFlat(true);
    muteBtn->setIconSize(QSize(20,20));
    lyricBtn = new QPushButton(tr("词"));
    lyricBtn->setFixedSize(20,20);
    currentTimeLable = new QLabel("00:00");
    remainingTimeLable = new QLabel("00:00");
    timeSlider = new QSlider(Qt::Horizontal);
    timeSlider->setStyleSheet("\
                              QSlider::groove:horizontal {\
                                  height: 4px;\
                                  background:transparent;\
                              }\
                              QSlider::handle:horizontal {\
                                  border: none;\
                                  border-image:url(:/point.ico);\
                                  width: 14px;\
                                  margin:-5px 0px -5px 0px;\
                              }\
                              QSlider::add-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(194,194,196);\
                              }\
                              QSlider::sub-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(232,60,60);\
                              }\
                              ");
    soundSlider = new QSlider(Qt::Horizontal);
    soundSlider->setRange(0,100);
    soundSlider->setValue(100);
    soundSlider->setFixedWidth(90);
    soundSlider->setStyleSheet("\
                              QSlider::groove:horizontal {\
                                  height: 4px;\
                                  background:transparent;\
                              }\
                              QSlider::handle:horizontal {\
                                  border-image: url(:/dot_red.ico);\
                                  border: none;\
                                  width: 8px;\
                                  margin:-2px 0px -2px 0px;\
                              }\
                              QSlider::add-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(194,194,196);\
                              }\
                              QSlider::sub-page:horizontal{\
                                  height: 4px;\
                                  border-radius: 2px;\
                                  background-color:rgb(232,60,60);\
                              }\
                              ");

    QHBoxLayout *hBoxLayout = new QHBoxLayout(statusWidget);
    hBoxLayout->addWidget(musicPlayerBtn);
    hBoxLayout->addWidget(previousBtn);
    hBoxLayout->addWidget(pauseBtn);
    hBoxLayout->addWidget(nextBtn);
    hBoxLayout->addWidget(currentTimeLable);
    hBoxLayout->addWidget(timeSlider);
    hBoxLayout->addWidget(remainingTimeLable);
    hBoxLayout->addWidget(muteBtn);
    hBoxLayout->addWidget(soundSlider);
    hBoxLayout->addWidget(lyricBtn);
}

void Player::createApi()            //API
{
    cloudMusicAPI = new CloudMusicAPI(this);
}

void Player::createTopListWidget()              //创建榜单
{
    topListWidget = new QWidget;
    QString json = cloudMusicAPI->getJson("http://music.163.com/api/toplist");
    QJsonDocument d = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject root = d.object();
    if (root["code"].toInt() == 200)
    {
        QHash<QString,QStringList> topList;
        QJsonArray list = root["list"].toArray();
        for (int i = 0;i < list.count();i++)
        {
            QJsonValue id = list.at(i).toObject()["id"];
            QJsonValue name = list.at(i).toObject()["name"];
            QJsonValue coverImgUrl = list.at(i).toObject()["coverImgUrl"];
            QJsonValue description = list.at(i).toObject()["description"];

            QStringList strList;
            strList << name.toString() << coverImgUrl.toString() << description.toString();
            topList.insert(QString::number(id.toDouble(),'s',0),strList);
        }
        QGridLayout *topListLayout = new QGridLayout(topListWidget);
        QHash<QString,QStringList>::const_iterator it;
        it = topList.constBegin();
        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < topList.size() / 4;j++)
            {
                QByteArray imgData = cloudMusicAPI->readImg(it.value().at(1));
                QPixmap pixmap;
                pixmap.loadFromData(imgData);
                pixmap = pixmap.scaled(64,64,Qt::KeepAspectRatioByExpanding);
                QLabel *img = new QLabel;
                img->setFixedSize(64,64);
                img->setPixmap(pixmap);
                img->setStyleSheet("QLable {border-radius:32px;background-color:red;}");
                QString btnWord = it.value().at(0);
                btnWord.replace(10,btnWord.size(),"...");
                QPushButton *button = new QPushButton(btnWord);
                button->setObjectName(it.value().at(0));
                button->setToolTip(QString(it.value().at(0)).append("\n").append(it.value().at(2)));
                button->setFlat(true);
                button->setCursor(Qt::PointingHandCursor);
                QVBoxLayout *vBoxLayout = new QVBoxLayout;
                vBoxLayout->addWidget(img,0,Qt::AlignHCenter);
                vBoxLayout->addWidget(button,0,Qt::AlignHCenter);
                topListLayout->addLayout(vBoxLayout,i,j);
                QString id = it.key();
                this->connect(button,&QPushButton::clicked,this,[=](){
                    QString jsonPlayList = cloudMusicAPI->getJson(QString("http://music.163.com/api/playlist/detail?id=").append(id));
                    QJsonDocument d = QJsonDocument::fromJson(jsonPlayList.toUtf8());
                    QJsonObject root = d.object();
                    if (root["code"].toInt() == 200)
                    {
                        if (!Dat::idListHash.isEmpty())
                        {
                            Dat::idListHash.clear();
                        }
                        QJsonObject result = root["result"].toObject();
                        QJsonArray tracks = result["tracks"].toArray();
                        for (int i = 0;i < tracks.size();i++)
                        {
                            QJsonValue id = tracks.at(i).toObject()["id"];
                            QJsonValue name = tracks.at(i).toObject()["name"];
                            QJsonArray artists = tracks.at(i).toObject()["artists"].toArray();
                            QString artistsName;
                            for (int j = 0;j < artists.size();j++)
                            {
                                artistsName.append(artists.at(j).toObject()["name"].toString());
                            }
                            QJsonObject album = tracks.at(i).toObject()["album"].toObject();
                            QJsonValue albumName = album["name"];
                            QJsonValue albumPicUrl = album["picUrl"];
                            QJsonValue duration = tracks.at(i).toObject()["duration"];
                            QStringList playList;
                            playList << name.toString() << artistsName << albumName.toString()
                                     << QString::number(duration.toDouble(),'s',0) << albumPicUrl.toString();
                            Dat::idListHash.insert(QString::number(id.toDouble(),'s',0),playList);
//                            qDebug()  << Dat::idListHash.size() << "之前：" << Dat::idListHash.value(QString::number(id.toDouble(),'s',0));
                        }
                        createMusicTableWidget(this->sender()->objectName());
                    }
                });
                it++;
            }
        }
    } else {
        new QLabel(tr("<h3>网络出错,请确认网络链接后重新启动！</h3>"),centerSCrollArea);
    }
}

void Player::createplayListWidget(int page)         //歌单
{
//    playListWidget = new QWidget;



    QObjectList listWidget = playListWidget->children();
    if (!listWidget.isEmpty())
    {
        for (int i = 0;i < listWidget.size();i++)
        {
            delete listWidget.at(i);
        }
    }

    QString json = cloudMusicAPI->getJson(QString("http://music.163.com/api/playlist/list?order=hot&limit=20&offset=%1").arg(QString::number(page)));
    QJsonDocument d = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject root = d.object();
    QVBoxLayout *vBoxLayOut = new QVBoxLayout(playListWidget);
    QGridLayout *topListLayout = new QGridLayout;
    vBoxLayOut->addLayout(topListLayout,8);
    if (root["code"].toInt() == 200)
    {

        if (root["more"].toBool())
        {
            static int page = 0;
            QHBoxLayout *hBoxLayout = new QHBoxLayout;
            QPushButton *listPreviousBtn = new QPushButton(tr("上一页"));
            this->connect(listPreviousBtn,&QPushButton::clicked,this,[=](){
                if (page > 0)
                {
                    createplayListWidget(--page * 20);
                    qDebug() << "上一页" << page;
                }
            });
            QPushButton *listNextBtn = new QPushButton(tr("下一页"));
            this->connect(listNextBtn,&QPushButton::clicked,this,[=](){

                createplayListWidget(++page * 20);
                qDebug() << "下一页" << page;
            });
            QLabel *pageLabel = new QLabel(tr("第%1页").arg(page+1));
            pageLabel->setFixedWidth(50);
            pageLabel->setAlignment(Qt::AlignCenter);
            hBoxLayout->addStretch(2);
            hBoxLayout->addWidget(listPreviousBtn,1);
            hBoxLayout->addWidget(pageLabel);
            hBoxLayout->addWidget(listNextBtn,1);
            hBoxLayout->addStretch(2);

            vBoxLayOut->addStretch(8);
            vBoxLayOut->addLayout(hBoxLayout,1);
            vBoxLayOut->setContentsMargins(0,10,0,10);
            vBoxLayOut->setSpacing(0);
        }

        QHash<QString,QStringList> topList;
        QJsonArray playlists = root["playlists"].toArray();
        for (int i = 0;i < playlists.size();i++)
        {
            QJsonValue id = playlists.at(i).toObject()["id"];
            QJsonValue name = playlists.at(i).toObject()["name"];
            QJsonValue description = playlists.at(i).toObject()["description"];
            QJsonValue coverImgUrl = playlists.at(i).toObject()["coverImgUrl"];

            QStringList strList;
            strList << name.toString() << coverImgUrl.toString() << description.toString();
            topList.insert(QString::number(id.toDouble(),'s',0),strList);
        }
        QHash<QString,QStringList>::const_iterator it;
        it = topList.constBegin();
        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < topList.size() / 4;j++)
            {
                QByteArray imgData = cloudMusicAPI->readImg(it.value().at(1));
                QPixmap pixmap;
                pixmap.loadFromData(imgData);
                pixmap = pixmap.scaled(64,64,Qt::KeepAspectRatioByExpanding);
                QLabel *img = new QLabel;
                img->setFixedSize(64,64);
                img->setPixmap(pixmap);
                img->setStyleSheet("QLable {border-radius:32px;background-color:red;}");
                QString btnWord = it.value().at(0);
                btnWord.replace(10,btnWord.size(),"...");
                QPushButton *button = new QPushButton(btnWord);
                button->setObjectName(it.value().at(0));
                button->setToolTip(QString(it.value().at(0)).append("\n").append(it.value().at(2)));
                button->setFlat(true);
                button->setCursor(Qt::PointingHandCursor);
                QVBoxLayout *vBoxLayout = new QVBoxLayout;
                vBoxLayout->addWidget(img,0,Qt::AlignHCenter);
                vBoxLayout->addWidget(button,0,Qt::AlignHCenter);
                topListLayout->addLayout(vBoxLayout,i,j);
                QString id = it.key();
                this->connect(button,&QPushButton::clicked,this,[=](){
                    QString jsonPlayList = cloudMusicAPI->getJson(QString("http://music.163.com/api/playlist/detail?id=").append(id));
                    QJsonDocument d = QJsonDocument::fromJson(jsonPlayList.toUtf8());
                    QJsonObject root = d.object();
                    if (root["code"].toInt() == 200)
                    {
                        if (!Dat::idListHash.isEmpty())
                        {
                            Dat::idListHash.clear();
                        }
                        QJsonObject result = root["result"].toObject();
                        QJsonArray tracks = result["tracks"].toArray();
                        for (int i = 0;i < tracks.size();i++)
                        {
                            QJsonValue id = tracks.at(i).toObject()["id"];
                            QJsonValue name = tracks.at(i).toObject()["name"];
                            QJsonArray artists = tracks.at(i).toObject()["artists"].toArray();
                            QString artistsName;
                            for (int j = 0;j < artists.size();j++)
                            {
                                artistsName.append(artists.at(j).toObject()["name"].toString());
                            }
                            QJsonObject album = tracks.at(i).toObject()["album"].toObject();
                            QJsonValue albumName = album["name"];
                            QJsonValue albumPicUrl = album["picUrl"];
                            QJsonValue duration = tracks.at(i).toObject()["duration"];
                            QStringList playList;
                            playList << name.toString() << artistsName << albumName.toString()
                                     << QString::number(duration.toDouble(),'s',0) << albumPicUrl.toString();
                            Dat::idListHash.insert(QString::number(id.toDouble(),'s',0),playList);
//                            qDebug()  << Dat::idListHash.size() << "之前：" << Dat::idListHash.value(QString::number(id.toDouble(),'s',0));
                        }
                        createMusicTableWidget(this->sender()->objectName());
                    }
                });
                it++;
            }
        }

    } else {
        new QLabel(tr("<h3>网络出错,请确认网络链接后重新启动！</h3>"),centerSCrollArea);
    }
}

void Player::createdjRadioWidget()          //主播电台
{
    djRadioWidget = new QWidget;
}

void Player::createAlbumWidget()            //新碟上架
{
    albumWidget = new QWidget;
}

void Player::createMusicPlayWidget()        //创建播放界面
{
    musicPlayWidget = new QWidget;
    musicPlayWidget->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/background.jpg")));
    musicPlayWidget->setPalette(pal);

    QLabel *musicTitle = new QLabel(tr("CloudMuisc of BC"));
    musicTitle->setFont(QFont("",15));
    musicTitle->setAlignment(Qt::AlignCenter);
    QTextBrowser *lyric = new QTextBrowser;
    lyric->setStyleSheet("background-color:rgba(0,0,0,0);"
                         "border:no-border;"
                         "font-size:12pt;");
    lyric->setAlignment(Qt::AlignCenter);
    lyric->append("极致音乐体验～");
    QVBoxLayout *mainLayout = new QVBoxLayout(musicPlayWidget);
    mainLayout->setContentsMargins(20,10,20,10);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(musicTitle,1);
    mainLayout->addWidget(lyric,9);
}

void Player::createMusicTableWidget(QString PlayListName)       //音乐列表
{
    stackWidget->setCurrentWidget(musicTableWidget);
    QObjectList listWidget = musicTableWidget->children();
    if (!listWidget.isEmpty())
    {
        for (int i = 0;i < listWidget.size();i++)
        {
            delete listWidget.at(i);
        }
    }
    QVBoxLayout *tableLayout = new QVBoxLayout(musicTableWidget);
    QLabel *MusicInformationLabel = new QLabel(tr("<font size='5'>%1</font>&nbsp;共0首音乐").arg(PlayListName));
    QPushButton *addPlayListBtn = new QPushButton(tr("播放全部"));
    this->connect(addPlayListBtn,&QPushButton::clicked,this,[=](){
        QHash<QString,QStringList>::const_iterator it;
        Dat::currentId = 0;
        if (!Dat::idPlayListHash.isEmpty())
        {
            Dat::idPlayListHash.clear();
        }
        for (it = Dat::idListHash.constBegin();it != Dat::idListHash.constEnd();it++)
        {
            addPlayList(it.key(),it.value().at(0));
        }
        Dat::currentId = 0;
        emit setMediaUrl(Dat::idPlayListHash[Dat::currentId].at(0));
        playerPause();
    });
    musicTable = new QTableView;
    musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    musicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    head = new QStandardItemModel;
    musicTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableLayout->addWidget(MusicInformationLabel,0,Qt::AlignLeft);
    tableLayout->addWidget(addPlayListBtn);
    tableLayout->addWidget(musicTable);
    QStringList headerLabel;
    headerLabel << tr("歌名") << tr("歌手") << tr("专辑") << tr("时长");
    head->setHorizontalHeaderLabels(headerLabel);
    musicTable->setModel(head);
    MusicInformationLabel->setText(tr("<font size='5'>%1</font>&nbsp;共%2首音乐").arg(PlayListName).arg(Dat::idListHash.size()));
    QHash<QString,QStringList>::const_iterator it = Dat::idListHash.begin();
    for (int i = 0;i < Dat::idListHash.size();i++,it++)
    {
        head->setItem(i,0,new QStandardItem(it.value().at(0)));
        head->setItem(i,1,new QStandardItem(it.value().at(1)));
        head->setItem(i,2,new QStandardItem(it.value().at(2)));
        int time = QString(it.value().at(3)).toInt()/1000;
        head->setItem(i,3,new QStandardItem(QString("%1分：%2秒").arg(time/60).arg(time%60)));

//        qDebug() << i << "数量：" << Dat::idListHash.size() << it.value();

    }
    QString style = "QHeaderView {background-color:white;}"
                    "QTableCornerButton::section{background-color:white;}";
    musicTable->setStyleSheet(style);
}


void Player::addPlayList(QString id,QString name)           //加入播放列表
{
    QStringList valueList;
    valueList << id << name;
    Dat::idPlayListHash.insert(Dat::currentId++,valueList);
}

//void Player::setMediaUrl(int id)        //设置音乐路径
//{
////    qDebug() << "size" << Dat::idPlayListHash.size();
////    qDebug() << "empty" << Dat::idPlayListHash.isEmpty();
////    if ((!Dat::idPlayListHash.isEmpty()) && (id < Dat::idPlayListHash.size()))
////    {
//////        musicPlayer->setMedia(QUrl(cloudMusicAPI->musicUrl(Dat::idPlayListHash[id].at(0))));
////        this
////    }
//}

void Player::playerPrevious()           //上一曲
{
    if (Dat::currentId > 0)
    {
        if (Dat::currentId == Dat::idPlayListHash.size())
        {
            Dat::currentId = Dat::currentId - 2;
            emit setMediaUrl(Dat::idPlayListHash[Dat::currentId].at(0));
        } else {
            emit setMediaUrl(Dat::idPlayListHash[--Dat::currentId].at(0));
        }

        musicPlayer->play();
        musicTable->selectRow(Dat::currentId);
    }
    qDebug() << "currentId:" << Dat::currentId;
}

void Player::playerPause()          //播放、暂停
{
    if (musicPlayer->state() == QMediaPlayer::PlayingState)
    {
        musicPlayer->pause();
//        pauseBtn->setIcon(QIcon(":/player_play.ico"));
    } else {
        musicPlayer->play();
//        pauseBtn->setIcon(QIcon(":/player_pause.ico"));
    }
    musicTable->selectRow(Dat::currentId);
}

void Player::playerNext()           //下一曲
{
    if (Dat::currentId < Dat::idPlayListHash.size() - 1)
    {
        emit setMediaUrl(Dat::idPlayListHash[++Dat::currentId].at(0));
        musicTable->selectRow(Dat::currentId);
        musicPlayer->play();
    }
    qDebug() << "currentId:" << Dat::currentId;

}

void Player::setMute()          //静音
{
    static bool flag = false;
    musicPlayer->setMuted(flag = !flag);
    if (flag)
    {
        soundSlider->setValue(0);
    } else {
        soundSlider->setValue(musicPlayer->volume());
    }
}

void Player::playerConnect()        //播放器逻辑槽
{
    static bool timeSliderReleasedFlag = true;
    this->connect(timeSlider,&QSlider::sliderPressed,this,[=](){
        timeSliderReleasedFlag = false;
    });
    this->connect(musicPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 position){        //进度条
        int totalT = int(musicPlayer->duration()/1000);
        int currentT = int(position/1000);
        int remainT = totalT - currentT;
        timeSlider->setRange(0,totalT);
        if (timeSliderReleasedFlag)
        {
            timeSlider->setValue(currentT);
        }
        currentTimeLable->setText(QString("%1:%2").arg(currentT/60,2,10,QLatin1Char('0'))
                                  .arg(currentT%60,2,10,QLatin1Char('0')));
        remainingTimeLable->setText(QString("%1:%2").arg(remainT/60,2,10,QLatin1Char('0'))
                                    .arg(remainT%60,2,10,QLatin1Char('0')));
//        qDebug() << "current:" << position << "totalT:" << musicPlayer->duration();

        if (position == musicPlayer->duration() && position != 0 && musicPlayer->duration() != 0)
        {
            if (++Dat::currentId < Dat::idPlayListHash.size())
            {
                emit setMediaUrl(Dat::idPlayListHash[Dat::currentId].at(0));
                musicTable->selectRow(Dat::currentId);
            }else {
                Dat::currentId = Dat::idPlayListHash.size();
            }
            qDebug() << "currentId:" << Dat::currentId;
        }
    });

    this->connect(musicPlayer,&QMediaPlayer::audioAvailableChanged,this,[=](){     //下一曲自动播放
//        qDebug() << "调用" << avilable;
        if (musicPlayer->state() != QMediaPlayer::PlayingState)
        {
            if (Dat::currentId < Dat::idPlayListHash.size())
            {
                musicPlayer->play();
            }
        }
    });

    this->connect(musicPlayer,&QMediaPlayer::stateChanged,this,[=](){           //播放器停止动作
        if (musicPlayer->state() == QMediaPlayer::StoppedState)
        {
            timeSlider->setValue(0);
            currentTimeLable->setText("00:00");
            remainingTimeLable->setText("00:00");
            pauseBtn->setIcon(QIcon(":/player_play.ico"));

            emit searchOrMusicNameShowSignal(true);
        }
        if (musicPlayer->state() == QMediaPlayer::PausedState)
        {
            pauseBtn->setIcon(QIcon(":/player_play.ico"));
            emit searchOrMusicNameShowSignal(true);
        }
        if (musicPlayer->state() == QMediaPlayer::PlayingState)
        {
            pauseBtn->setIcon(QIcon(":/player_pause.ico"));
            emit searchOrMusicNameShowSignal(false);
        }
    });
    this->connect(this,&Player::setMediaUrl,cloudMusicAPI,&CloudMusicAPI::getMusicUrl);     //get music url
    this->connect(cloudMusicAPI,&CloudMusicAPI::musicUrl,this,[=](QString url){        //setMedia
        if (url.endsWith("404"))
        {
            playerNext();
        }
        musicPlayer->setMedia(QUrl(url));
    });

    this->connect(previousBtn,&QPushButton::clicked,this,&Player::playerPrevious);     //上一曲
    this->connect(pauseBtn,&QPushButton::clicked,this,&Player::playerPause);       //暂停
    this->connect(nextBtn,&QPushButton::clicked,this,&Player::playerNext);         //下一曲
    this->connect(muteBtn,&QPushButton::clicked,this,&Player::setMute);             //静音
    this->connect(timeSlider,&QSlider::sliderReleased,this,[=](){           //快进、快退
        if (musicPlayer->state() == QMediaPlayer::PlayingState)
        {
//            qDebug() << "value" << timeSlider->value();
            musicPlayer->setPosition(timeSlider->value()*1000);
            timeSliderReleasedFlag = true;
        }
    });
    this->connect(soundSlider,&QSlider::valueChanged,this,[=](){        //音量调节
        qDebug() << "音量" << musicPlayer->volume() << soundSlider->value();
        if (soundSlider->value() != 0)
        {
            musicPlayer->setVolume(soundSlider->value());
            muteBtn->setIcon(QIcon(":/sound_on.ico"));
        } else {
            muteBtn->setIcon(QIcon(":/sound_off.ico"));
        }
    });

    this->connect(this,&Player::searchOrMusicNameShowSignal,this,[=](bool flag){
        if ((musicPlayer->state() == QMediaPlayer::PlayingState))
        {
            if (flag)
            {
                if (searchLineEdit->isHidden())       //搜索
                {
                    searchLineEdit->show();
                    searchBtn->setStyleSheet("background-color:rgb(168,40,40);border-radius:10px;"
                                                        "text-align:right;padding-right:10px;");
                    searchBtn->setIconSize(QSize(15,15));
                    searchBtn->setText("");
                }
            }else {         //歌名
                if (!searchLineEdit->isHidden())
                {
                    searchLineEdit->hide();
                }
                searchBtn->setStyleSheet("background-color:rgb(198,47,47);"
                                                   "font-size:10pt;");
                searchBtn->setIconSize(QSize(0,0));
                QString name = Dat::idPlayListHash[Dat::currentId].at(1);
                searchBtn->setText(tr("正在播放：").append(name));
            }
        }else {
            if (searchLineEdit->isHidden())
            {
                searchLineEdit->show();
                searchBtn->setStyleSheet("background-color:rgb(168,40,40);border-radius:10px;"
                                                    "text-align:right;padding-right:10px;");
                searchBtn->setIconSize(QSize(15,15));
                searchBtn->setText("");
            }
        }
    });

    this->connect(titleWidget,&TitleWidget::sendEPos,this,[=](QPoint ePos){
        if ((ePos.x() >= searchBtn->pos().x() - 5) &&
                (ePos.x() <= (searchBtn->pos().x() + searchBtn->width() + 5)) &&
                (ePos.y() >= (searchBtn->pos().y() - 5)) &&
                (ePos.y() <= (searchBtn->pos().y() + searchBtn->height() + 5)))
        {
            emit searchOrMusicNameShowSignal(true);     //搜索
        } else {
            emit searchOrMusicNameShowSignal(false);    //歌名
        }
    });
}
