#include "titlewidget.h"
#include <QIcon>
#include <QApplication>
#include <QPalette>
#include <QFontDatabase>
#include <QDebug>

const QSize LOGOSIZE { 36,36 };
const QSize ICONSIZE { 20,20 };

TitleWidget::TitleWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

TitleWidget::~TitleWidget()
{
    cloudMusicBtn->deleteLater();
    searchLineEdit->deleteLater();
    searchBtn->deleteLater();
    minimizeBtn->deleteLater();
    maximizeBtn->deleteLater();
    closeBtn->deleteLater();
    mainLayout->deleteLater();
    settingBtn->deleteLater();
}

//顶部界面初始化
void TitleWidget::initUI()
{
//    this->setFixedHeight(50);
    this->setFixedHeight(43);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(198,47,47));
    this->setPalette(pal);

    cloudMusicBtn = new QPushButton(QIcon(":/icons/cloud_music_logo.ico")
                                    ,tr("CloudMusic of BC"));
    cloudMusicBtn->setIconSize(LOGOSIZE);
    cloudMusicBtn->setFlat(true);
    cloudMusicBtn->setToolTip(tr("主页"));

#ifdef Q_OS_LINUX
    QFontDatabase::addApplicationFont("./fonts/华文隶书.ttf");
#endif
    cloudMusicBtn->setStyleSheet("QPushButton {font-family:STLiti;font-size:16pt;}"
                                 "QPushButton:pressed {background-color:rgb(198,47,47);}");
    connect(cloudMusicBtn,&QPushButton::clicked,[=](){
        emit cloudMusicBtn_clicked(0);          //首页界面 :0
    });

    searchBtn = new QPushButton;
    searchBtn->setFixedSize(215,20);
    searchBtn->setIcon(QIcon(":/icons/search.ico"));
    searchBtn->setIconSize(QSize(15,15));
    searchBtn->setFlat(true);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setStyleSheet("background-color:rgb(168,40,40);border-radius:10px;"
                                 "text-align:right;padding-right:10px;");

    searchLineEdit = new QLineEdit(searchBtn);
    searchLineEdit->setFixedSize(190,20);
    searchLineEdit->setPlaceholderText(tr("搜索音乐，歌手，歌词，用户"));
    searchLineEdit->setStyleSheet("background-color:rgb(168,40,40);color:rgb(199,115,115);"
                                       "border-top-left-radius:10px;border-bottom-left-radius:10px;");

    loginBtn = new QPushButton;
    loginBtn->setText(tr("未登录"));
    loginBtn->setIcon(QIcon(":/icons/avatar_default.ico"));
    loginBtn->setFlat(true);
    loginBtn->setIconSize(ICONSIZE);

    settingBtn = new QPushButton;
    settingBtn->setIcon(QIcon(":/icons/settings.ico"));
    settingBtn->setFlat(true);
    settingBtn->setIconSize(ICONSIZE);
    settingBtn->setToolTip(tr("设置"));

    minimizeBtn = new QPushButton;
    minimizeBtn->setIcon(QIcon(":/icons/window_min_size.ico"));
    minimizeBtn->setIconSize(ICONSIZE);
    minimizeBtn->setFlat(true);
    minimizeBtn->setToolTip(tr("最小化窗口"));

    //最小化主窗口
    connect(minimizeBtn,&QPushButton::clicked,this,[=](){
        emit window_size_control(true);
    });

    maximizeBtn = new QPushButton;
    maximizeBtn->setIcon(QIcon(":/icons/window_max_size.ico"));
    maximizeBtn->setIconSize(ICONSIZE);
    maximizeBtn->setFlat(true);
    maximizeBtn->setToolTip(tr("最大化窗口"));

    //最大化窗口
    connect(maximizeBtn,&QPushButton::clicked,this,&TitleWidget::on_maximizeBtn_press_slot);

    closeBtn = new QPushButton;
    closeBtn->setIcon(QIcon(":/icons/window_close.ico"));
    closeBtn->setIconSize(ICONSIZE);
    closeBtn->setFlat(true);
    closeBtn->setToolTip(tr("关闭窗口"));

    //关闭主窗口
    connect(closeBtn,&QPushButton::clicked,this,[=](){
        QApplication::quit();
    });

    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    mainLayout->addWidget(cloudMusicBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(searchBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(loginBtn);
    mainLayout->addWidget(settingBtn);
    mainLayout->addWidget(minimizeBtn);
    mainLayout->addWidget(maximizeBtn);
    mainLayout->addWidget(closeBtn);

}

/*
void TitleWidget::mousePressEvent(QMouseEvent *e)
{
     mainWidgetPtr = (QWidget*)this->parent() ;
    if (e->button() == Qt::LeftButton)
    {
        qDebug() << "mousePoint:" << mainWidgetPtr->pos() << " , " << "globalpos:" << e->globalPos();
        mousePoint = e->globalPos() - mainWidgetPtr->pos();
        e->accept();
        dragWindow = true;
    }
    return QWidget::mousePressEvent(e);
}

void TitleWidget::mouseReleaseEvent(QMouseEvent *)
{
    dragWindow = false;
    mainWidgetPtr = nullptr;
}

void TitleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (dragWindow && (e->buttons() && Qt::LeftButton))
    {
        mainWidgetPtr->move(e->globalPos() - mousePoint);
    }
    return QWidget::mouseMoveEvent(e);
}
*/

void TitleWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    on_maximizeBtn_press_slot();
    return QWidget::mouseDoubleClickEvent(e);
}


//最大化按钮槽函数
void TitleWidget::on_maximizeBtn_press_slot()
{
    emit window_size_control(false);
    static bool ok { false };
    ok = !ok;
    if (ok)
    {
        maximizeBtn->setToolTip(tr("还原窗口"));
        maximizeBtn->setIcon(QIcon(":/icons/window-restore.ico"));
    }
    else
    {
        maximizeBtn->setToolTip(tr("最大化窗口"));
        maximizeBtn->setIcon(QIcon(":/icons/window_max_size.ico"));
    }
}
