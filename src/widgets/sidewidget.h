#ifndef SIDEWIDGET_H
#define SIDEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QResizeEvent>

class SideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SideWidget(QWidget *parent = nullptr);
    ~SideWidget();
    void initUI();
    void addWidget(QWidget *);

private:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public:
    QWidget *musicNameWidget;
    QLabel *musicNameLabel;
    QPushButton *musicInfoBtn;

private:
    QVBoxLayout *mainLayout;

signals:
    void btn_clicked(int);

public slots:
    void on_btn_clicked();
};

#endif // SIDEWIDGET_H
