#include "Player.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMovie>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix(":/start.gif");
    QSplashScreen splash(pix);
    QLabel label(&splash);
    QMovie mv(":/start.gif");
    label.setMovie(&mv);
    mv.start();
    splash.show();
    Player w;
    w.setWindowIcon(QIcon(":/cloud_music_logo.ico"));
    w.show();
    splash.finish(&w);

    return a.exec();
}
