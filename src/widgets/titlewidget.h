#ifndef TitleWidget_H
#define TitleWidget_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = nullptr);
    ~TitleWidget();
    void initUI();

protected:
    /*
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    */
    void mouseDoubleClickEvent(QMouseEvent *);

public:
//    QLabel *musicNameLabel;


private:
    QPushButton *cloudMusicBtn;
    QPushButton *searchBtn;
    QLineEdit *searchLineEdit;
    QPushButton *loginBtn;
    QPushButton *settingBtn;
    QPushButton *minimizeBtn;
    QPushButton *maximizeBtn;
    QPushButton *closeBtn;

    QHBoxLayout *mainLayout;

    QPoint mousePoint;
    bool dragWindow { false };

    QWidget *mainWidgetPtr;

signals:
    void window_size_control(const bool);
    void cloudMusicBtn_clicked(int);

public slots:
    void on_maximizeBtn_press_slot();
};

#endif // TitleWidget_H
