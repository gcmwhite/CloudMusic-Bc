#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QRect>
#include <QStackedLayout>
#include <QResizeEvent>
#include "titlewidget.h"
#include "sidewidget.h"
#include "bottomwidget.h"
#include "toplistwidget.h"
#include "../music_api/neteaseapi.h"
#include "albumwidget.h"
#include "musiclistwidget.h"
#include "djradiowidget.h"
#include "topplaylistwidget.h"
#include "playerwidget.h"
#include "../player/aplyer.h"
#include "musicplaylisttable.h"
#include "../player/playlist.h"
#include "musicnamewidget.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void initUI();
    void initAPI();

private:
    bool eventFilter(QObject *, QEvent *);
    void x11Move(int,int);
    void resizeEvent(QResizeEvent *);

private:
    //主界面
    TitleWidget *titleWidget;
    SideWidget *sideWidget;
    QStackedWidget *stackWidgets;
    QWidget *mainCenterWidget;
    QWidget *centerWidget;
    PlayerWidget *playerWidget;
    BottomWidget *bottomWidget;
    QStackedLayout *mainStackedLayout;
    MusicPlayListTable *musicPlayListTable;
    MusicNameWidget *musicNameWidget;

    //Player
    APlyer *aPlyer;
    PlayList *playList;

    //API
    NetEaseApi *netEaseApi;

    //stackwidgets
    TopListWidget *topListWidget;                                   //榜单
    TopPlayListWidget *topPlayListWidget;                           //歌单
    DJRadioWidget *djRadioWidget;                                   //主播电台
    AlbumWidget *albumWidget;                                       //新碟上架
    MusicListWidget *musicListWidget;         //播放列表


    //主布局
    QVBoxLayout *mainLayout;

    //窗口缩放鼠标位置、鼠标按下标志位、窗口位置
    QPoint window_zoom_mouse_point;
    bool window_zoom_mouse_press_flag { false };
    bool window_zoom_mouse_inside_flag { false };
    QRect window_zoom_location;

public slots:
    void setCurrentWidget(int);
    void get_music_list(const QString &);

};

#endif // MAINWIDGET_H
