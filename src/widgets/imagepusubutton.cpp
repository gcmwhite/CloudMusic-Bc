#include "imagepusubutton.h"
#include <QVBoxLayout>
#include <QSize>
#include <QBitmap>
#include <QPainter>

ImagePusuButton::ImagePusuButton(const QString &text, QWidget *parent)
    :QPushButton(parent)
{
    this->setMinimumSize(90,90);
    this->setFlat(true);
//    this->setCursor(Qt::PointingHandCursor);
    mainLayout = new QVBoxLayout(this);
    pixLabel = new QLabel;
    textLabel = new QLabel;
    textLabel->setText(text);
    textLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(pixLabel);
    mainLayout->addWidget(textLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);


}

QPixmap ImagePusuButton::pixmapToRound(const QPixmap &pix, int radius)
{
    if (pix.isNull())
        return QPixmap();
    QSize size(2*radius,2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0,0,size.width(),size.height(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(0,0,size.width(),size.height(),99,99);
    painter.end();
    QPixmap image = pix.scaled(size);
    image.setMask(mask);
    return image;
}

void ImagePusuButton::setImg(const QPixmap &pix)
{
    QPixmap image = pix.scaled(750,750,Qt::KeepAspectRatio);
    image = pixmapToRound(image,image.width()/22);
    pixLabel->setPixmap(image);
    pixLabel->setAlignment(Qt::AlignCenter);
}
