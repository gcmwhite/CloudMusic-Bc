#ifndef IMAGEPUSUBUTTON_H
#define IMAGEPUSUBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

class ImagePusuButton : public QPushButton
{
    Q_OBJECT
public:
    ImagePusuButton(const QString &,QWidget *parent = nullptr);
    void setImg(const QPixmap &);

private:
    QPixmap pixmapToRound(const QPixmap &,int);


private:
    QLabel *pixLabel;
    QLabel *textLabel;
    QVBoxLayout *mainLayout;
};

#endif // IMAGEPUSUBUTTON_H
