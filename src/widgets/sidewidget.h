#ifndef SIDEWIDGET_H
#define SIDEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QVBoxLayout>

class SideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SideWidget(QWidget *parent = nullptr);
    ~SideWidget();
    void initUI();
    void paintEvent(QPaintEvent *);
    void addWidget(QWidget *);

private:
    QVBoxLayout *mainLayout;

signals:
    void btn_clicked(int);

public slots:
    void on_btn_clicked();
};

#endif // SIDEWIDGET_H
