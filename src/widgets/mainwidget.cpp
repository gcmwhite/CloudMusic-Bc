#include "mainwidget.h"
#include <QDebug>
#include <QTimer>
#include <QMovie>
#include <QHBoxLayout>
#include <X11/Xlib.h>
#include <QX11Info>
#include <QScreen>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    aPlyer = new APlyer(this);
    initUI();
    musicPlayListTable = new MusicPlayListTable(this);
    QTimer *netStartTimer = new QTimer(this);
    connect(netStartTimer,&QTimer::timeout,this,[=](){
        initAPI();
        netStartTimer->stop();
    });
    netStartTimer->start(300);

    //widgets切换
    connect(sideWidget,&SideWidget::btn_clicked,stackWidgets,&QStackedWidget::setCurrentIndex);

    //进度条控制
    static bool timeSliderPressFlag = false;
    connect(bottomWidget->timeSlider,&QSlider::sliderPressed,[=](){
        timeSliderPressFlag = true;
    });
    connect(bottomWidget->timeSlider,&QSlider::sliderReleased,[=](){
        aPlyer->setPosition(qint64(bottomWidget->timeSlider->value()*1000));
        timeSliderPressFlag = false;
    });

    //进度条、时间显示
    connect(aPlyer,&APlyer::positionChanged,[=](qint64 position){
        int currentT = int(position/1000);
        int remainT = int((aPlyer->duration()-position)/1000);
        if (position == 0)
        {
            bottomWidget->timeSlider->setRange(0,int(aPlyer->duration()/1000));
        }
        if (!timeSliderPressFlag)
            bottomWidget->timeSlider->setValue(currentT);
        bottomWidget->currentTimeLable->setText(QString("%1:%2").arg(currentT/60,2,10,QLatin1Char('0'))
                                    .arg(currentT%60,2,10,QLatin1Char('0')));
        bottomWidget->remainingTimeLable->setText(QString("%1:%2").arg(remainT/60,2,10,QLatin1Char('0'))
                                    .arg(remainT%60,2,10,QLatin1Char('0')));
    });

    //播放器控制
    connect(bottomWidget->previousBtn,&QPushButton::clicked,this,[=](){
        aPlyer->previous__();
    });
    connect(bottomWidget->playBtn,&QPushButton::clicked,this,[=](){
        aPlyer->play__();
    });
    connect(bottomWidget->nextBtn,&QPushButton::clicked,this,[=](){
        aPlyer->next__();
    });

    //播放按钮
    connect(aPlyer,&APlyer::stateChanged,this,[=](QMediaPlayer::State newState){
        switch (newState) {
        case QMediaPlayer::PlayingState:
            bottomWidget->playBtn->setIcon(QIcon(":/icons/player_pause.ico"));
            break;
        case QMediaPlayer::PausedState:
            bottomWidget->playBtn->setIcon(QIcon(":/icons/player_play.ico"));
        case QMediaPlayer::StoppedState:
            bottomWidget->playBtn->setIcon(QIcon(":/icons/player_play.ico"));
            bottomWidget->timeSlider->setValue(0);
            bottomWidget->currentTimeLable->setText("00:00");
            bottomWidget->remainingTimeLable->setText("00:00");
            break;
        }
    });

    //音量设置
    connect(bottomWidget->soundSlider,&QSlider::valueChanged,[=](int sound){
        aPlyer->setVolume(sound);
    });

    //静音
    connect(bottomWidget->muteBtn,&QPushButton::clicked,[=](){
        static bool flag = false;
        flag = !flag;
        aPlyer->setMuted(flag);
        if (flag)
        {
            bottomWidget->muteBtn->setIcon(QIcon(":/icons/sound_off.ico"));
        } else {
            bottomWidget->muteBtn->setIcon(QIcon(":/icons/sound_on.ico"));
        }
    });

    connect(musicPlayListTable,&MusicPlayListTable::countChanged,[=](int count){
        bottomWidget->playlistBtn->setText(QString::number(count));
    });

    connect(bottomWidget->playlistBtn,&QPushButton::clicked,[=](){
        static bool flag = false;
        flag = !flag;
        musicPlayListTable->setVisible(flag);
    });

    connect(aPlyer,&APlyer::indexChanged,musicPlayListTable,&MusicPlayListTable::selectRow);
    connect(musicPlayListTable,&MusicPlayListTable::doubleClicked,this,[=](){
        aPlyer->play__(musicPlayListTable->currentIndex().row());
    });
}

MainWidget::~MainWidget()
{
//    titleWidget->deleteLater();
//    sideWidget->deleteLater();
//    stackWidgets->deleteLater();
//    bottomWidget->deleteLater();
//    mainLayout->deleteLater();

}

//主界面初始化
void MainWidget::initUI()
{
    this->resize(1000,710);
    this->setWindowFlags(Qt::FramelessWindowHint);        //界面无边框
    this->setWindowTitle(tr("网易云音乐"));
    this->setWindowIcon(QIcon(":/icons/cloud_music_logo.ico"));

    titleWidget = new TitleWidget;
    titleWidget->installEventFilter(this);

    //窗口控制槽
    connect(titleWidget,&TitleWidget::window_size_control,this,[=](const bool ok){
        if (ok)
            this->showMinimized();
        else
            if (this->isMaximized())
                this->showNormal();
            else
                this->showMaximized();
    });

    //切换界面
    connect(titleWidget,&TitleWidget::cloudMusicBtn_clicked,this,&MainWidget::setCurrentWidget);

    sideWidget = new SideWidget;    
    stackWidgets = new QStackedWidget;
    QLabel *loading_label = new QLabel;
    QMovie *movie = new QMovie(":/imgs/loading.gif");
    loading_label->setMovie(movie);
    loading_label->setAlignment(Qt::AlignCenter);
    movie->start();
    stackWidgets->addWidget(loading_label);             //添加loading界面 :0

    centerWidget = new QWidget;
    QHBoxLayout *hBoxLayout = new QHBoxLayout(centerWidget);
    hBoxLayout->addWidget(sideWidget);
    hBoxLayout->addWidget(stackWidgets);
    hBoxLayout->setMargin(0);
    hBoxLayout->setSpacing(0);

    playerWidget = new PlayerWidget;

    mainCenterWidget = new QWidget;

    bottomWidget = new BottomWidget;
    bottomWidget->installEventFilter(this);

    //切换界面
    connect(bottomWidget,&BottomWidget::musicPlayerBtn_clicked,this,&MainWidget::setCurrentWidget);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(titleWidget);
    mainLayout->addWidget(mainCenterWidget);
    mainLayout->addWidget(bottomWidget);


    mainStackedLayout = new QStackedLayout(mainCenterWidget);
    mainStackedLayout->addWidget(centerWidget);
    mainStackedLayout->addWidget(playerWidget);
    mainStackedLayout->setCurrentWidget(centerWidget);

}

//网络和stackwidget
void MainWidget::initAPI()
{
    netEaseApi = new NetEaseApi(this);
    musicListWidget = new MusicListWidget;
    stackWidgets->addWidget(musicListWidget);        //添加播放列表 :1

    topListWidget = new TopListWidget(netEaseApi->top_list());
    stackWidgets->addWidget(topListWidget);                     //添加榜单界面 :2
    stackWidgets->setCurrentWidget(topListWidget);

    topPlayListWidget = new TopPlayListWidget;
    topPlayListWidget->list(netEaseApi->top_playlist());
    //切换歌单分页
    connect(topPlayListWidget,&TopPlayListWidget::switch_page,[=](int index){
        topPlayListWidget->list(netEaseApi->top_playlist(index));
    });
    stackWidgets->addWidget(topPlayListWidget);                 //添加歌单界面 :3

    djRadioWidget = new DJRadioWidget;
    stackWidgets->addWidget(djRadioWidget);                     //添加主播电台 :4

    albumWidget = new AlbumWidget;
    stackWidgets->addWidget(albumWidget);                       //添加新碟上架 :5

    //榜单歌曲列表
    connect(topListWidget,&TopListWidget::top_list_id,this,&MainWidget::get_music_list);

    //歌单歌曲列表
    connect(topPlayListWidget,&TopPlayListWidget::top_playlist_id,this,&MainWidget::get_music_list);

    //播放选中列表歌曲
    connect(musicListWidget,static_cast<void (MusicListWidget::*)(const int,const QString &,const QStringList &)>
            (&MusicListWidget::addList),
            [=](const int index,const QString &listId,const QStringList &idList){
        aPlyer->addPlayList__(index,listId,idList);
    });

    //更新播放列表
    connect(musicListWidget,static_cast<void (MusicListWidget::*)(const QVector<QStringList> &)>(&MusicListWidget::addList),
            musicPlayListTable,static_cast<void (MusicPlayListTable::*)(const QVector<QStringList> &)>(&MusicPlayListTable::update_list));
}

bool MainWidget::eventFilter(QObject *obj, QEvent *e)
{
    //窗口最大化状态禁止操作
    if (this->isMaximized())
        return QObject::eventFilter(obj,e);
    //无边框移动
    static bool preeFlag = false;
    if (obj == titleWidget)
    {
        if (e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *event { (QMouseEvent *)e };
            if (event->buttons() & Qt::LeftButton)
            {
                preeFlag = true;
                event->accept();
                return true;
            }
        } else if (e->type() == QEvent::MouseButtonRelease)
        {
            preeFlag = false;
            e->accept();
            return true;
        } else if (e->type() == QEvent::MouseMove)
        {
            if (preeFlag)
            {
                QPoint point = QCursor::pos();
                x11Move(point.x(),point.y());
            }
            e->accept();
            return true;
        }
    }

    //无边框缩放
    else if (obj == bottomWidget)
    {
        if (e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *event { (QMouseEvent *)e };
            if (event->buttons() & Qt::LeftButton)
            {
                window_zoom_mouse_point = event->globalPos();
                window_zoom_location = this->geometry();
                window_zoom_mouse_press_flag = true;
                event->accept();
                return true;
            }
        }else if (e->type() == QEvent::MouseButtonRelease)
        {
            window_zoom_mouse_press_flag = false;
            window_zoom_mouse_inside_flag = false;
            return true;
        }else if (e->type() == QEvent::MouseMove)
        {
            QMouseEvent *event { (QMouseEvent *)e };
            if (bottomWidget->width() - event->x() <= 10 && bottomWidget->height() - event->y() <= 10)
            {
                window_zoom_mouse_inside_flag = true;
                bottomWidget->setCursor(Qt::SizeFDiagCursor);
            } else {
                bottomWidget->setCursor(Qt::ArrowCursor);
                if (!window_zoom_mouse_press_flag)
                    window_zoom_mouse_inside_flag = false;
            }
            if (window_zoom_mouse_press_flag && window_zoom_mouse_inside_flag)
            {
                int dx { event->globalX() - window_zoom_mouse_point.x() };
                int dy { event->globalY() - window_zoom_mouse_point.y() };
                QRect rc { window_zoom_location };
                rc.setRight(rc.right() + dx);
                rc.setBottom(rc.bottom() + dy);
                setGeometry(rc);
                update();
                return true;
            }
        }
    }
    return QObject::eventFilter(obj,e);
}

void MainWidget::setCurrentWidget(int index)
{
    mainStackedLayout->setCurrentIndex(index);
}

void MainWidget::get_music_list(const QString &id)
{
    stackWidgets->setCurrentWidget(musicListWidget);
    QString json = netEaseApi->playlist_detail(id);
    musicListWidget->playlist_detail(json);
}

//无边框移动
void MainWidget::x11Move(const int x,const int y)
{
    Display *display = QX11Info::display();
    XEvent xev;
    xev.xclient.type = ClientMessage;
    xev.xclient.message_type = XInternAtom(display, "_NET_WM_MOVERESIZE", False);
    xev.xclient.display = display;
    xev.xclient.window = winId();
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = x;
    xev.xclient.data.l[1] = y;
    xev.xclient.data.l[2] = 8;
    xev.xclient.data.l[3] = Button1;
    xev.xclient.data.l[4] = 0;
    XUngrabPointer(display, QX11Info::appTime());
    XSendEvent(display, QX11Info::appRootWindow(QX11Info::appScreen()), False,
               SubstructureRedirectMask | SubstructureNotifyMask, &xev);
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    int x = this->width() - musicPlayListTable->width();
    int y = this->height() - musicPlayListTable->height() - bottomWidget->height();
    musicPlayListTable->move(x,y);
}


