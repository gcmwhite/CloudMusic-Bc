#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>

class BottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = nullptr);
    ~BottomWidget();
    void initUI();

protected:
    void paintEvent(QPaintEvent *);
    /*
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    */

private:

    QHBoxLayout *mainLayout;

    bool pressMouseFlag { false };

    QWidget *mainWidgetPtr;

    QPoint mousePoint;

    QRect originGeometry;

public:
    QPushButton *musicPlayerBtn;
    QPushButton *previousBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *muteBtn;
    QPushButton *lyricBtn;
    QPushButton *playlistBtn;
    QLabel *currentTimeLable;
    QLabel *remainingTimeLable;
    QSlider *timeSlider;
    QSlider *soundSlider;

signals:
    void musicPlayerBtn_clicked(int);

};

#endif // BOTTOMWIDGET_H
