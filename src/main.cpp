#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include "widgets/mainwidget.h"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    MainWidget w;
    w.show();

    return app.exec();
}



