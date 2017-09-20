#ifndef PLAYER_H
#define PLAYER_H

#include "leftcontrolwidget.h"
#include "titlewidget.h"
#include "statuswidget.h"
#include "cloudmusicapi.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QMediaPlayer>

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();

protected:
    void createMainWidget();                //创建主界面
    void createTitleWidget();               //创建标题栏
    void createLeftControlWidget();         //创建左控栏
    void creatwCenterWidget();              //创建中央布局
    void createStatusWidget();              //创建状态栏
    void createTopListWidget();             //榜单界面
    void createplayListWidget(int);            //歌单界面
    void createdjRadioWidget();             //主播电台
    void createAlbumWidget();               //新碟上架
    void createMusicPlayWidget();           //创建播放界面
    void createMusicTableWidget(QString);          //创建音乐列表
    void createApi();                       //API
    void playerInit();                      //初始化
    void addPlayList(QString, QString);     //加入播放列表
    void playerConnect();                   //播放器逻辑槽




private:
    QVBoxLayout *mainLayout;
    LeftControlWidget *leftControlWidget;   //左控栏
    QScrollArea *leftControlScrollArea;     //左边滚动栏
    QScrollArea *centerSCrollArea;          //中央滚动栏
    TitleWidget *titleWidget;               //标题栏
    StatusWidget *statusWidget;             //状态栏

    //标题栏-title控件
    QPushButton *windowCloseBtn;            //关闭窗口
    QPushButton *windowMaxSizeBtn;          //最大化窗口
    QPushButton *windowMinSizeBtn;          //最小化窗口
    QPushButton *titleBtn;                  //首页
    QPushButton *searchBtn;                 //搜索按钮
    QLineEdit *searchLineEdit;              //搜索框

    //状态栏-status控件
    QPushButton *musicPlayerBtn;            //播放界面按钮
    QPushButton *previousBtn;               //上一曲
    QPushButton *pauseBtn;                  //暂停
    QPushButton *nextBtn;                   //下一曲
    QPushButton *muteBtn;                   //静音
    QPushButton *lyricBtn;                  //歌词
    QLabel *currentTimeLable;               //当前时间
    QLabel *remainingTimeLable;             //剩余时间
    QSlider *timeSlider;                    //进度条
    QSlider *soundSlider;                   //音量条

    //左控栏-leftControl控件
    QLabel *recommendLabel;                 //推荐
    QPushButton *topListBtn;                //排行榜
    QPushButton *playListBtn;               //歌单
    QPushButton *djRadioBtn;                //主播电台
    QPushButton *albumBtn;                  //新碟上架

    //中央布局
    QStackedWidget *stackWidget;            //堆叠窗口
    QWidget *topListWidget;                 //音乐榜单
    QWidget *playListWidget;                //歌单
    QWidget *djRadioWidget;                 //主播电台
    QWidget *albumWidget;                   //新碟上架
    QWidget *musicPlayWidget;               //播放界面
    QWidget *musicTableWidget;              //音乐列表

    //网络事件
    CloudMusicAPI *cloudMusicAPI;           //网易云api

    //音乐列表
    QTableView *musicTable;                 //音乐列表
    QStandardItemModel *head;               //表头

    //播放器控制
    QMediaPlayer *musicPlayer;              //播放器

public slots:
    void playerPause();                     //播放、暂停
    void playerPrevious();                  //上一曲
    void playerNext();                      //下一曲
    void setMute();                         //静音

signals:
    void setMediaUrl(QString);                  //设置音乐路径
    void searchOrMusicNameShowSignal(bool);

};

#endif // PLAYER_H
