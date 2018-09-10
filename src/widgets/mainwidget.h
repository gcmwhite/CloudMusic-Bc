#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QRect>
#include <QStackedLayout>
#include "titlewidget.h"
#include "sidewidget.h"
#include "bottomwidget.h"
#include "toplistwidget.h"
#include "../music_api/neteaseapi.h"
#include "albumwidget.h"
#include "currentmusicplaylistwidget.h"
#include "djradiowidget.h"
#include "topplaylistwidget.h"
#include "playerwidget.h"
#include "../player/aplyer.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void initUI();
    void initAPI();

protected:
    bool eventFilter(QObject *, QEvent *);
    void x11Move(int,int);

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

    //Player
    APlyer *aPlyer;

    //API
    NetEaseApi *netEaseApi;

    //stackwidgets
    TopListWidget *topListWidget;                                   //榜单
    TopPlayListWidget *topPlayListWidget;                           //歌单
    DJRadioWidget *djRadioWidget;                                   //主播电台
    AlbumWidget *albumWidget;                                       //新碟上架
    CurrentMusicPlayListWidget *currentMusicPlayListWidget;         //播放列表


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
