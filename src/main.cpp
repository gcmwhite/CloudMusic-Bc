#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include "widgets/imagepusubutton.h"
#include "widgets/mainwidget.h"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    MainWidget w;
    w.show();

    return app.exec();
}







/*
#include "widgets/toplistwidget.h"
#include "music_api/neteaseapi.h"
#include <QApplication>
#include <QDebug>
#include "widgets/mainwidget.h"

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    NetEaseApi api;
    TopListWidget *top = new TopListWidget(api.top_list());
    top->show();

    return a.exec();
}

*/








/*

#include <QApplication>
#include <QDebug>
#include "widgets/mainwidget.h"

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    MainWidget mw;
    mw.show();

    return a.exec();
}

*/


