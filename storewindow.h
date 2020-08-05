#ifndef STOREWINDOW_H
#define STOREWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include "variables.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

namespace Ui {
class StoreWindow;
}

class StoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StoreWindow(QWidget *parent = nullptr);
    void Init();
    Ui::StoreWindow *ui;
    int count;
    ~StoreWindow();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QImage ImgNpcOld;
    QImage ImgNpcRed;
    QImage ImgStoreMiddle;
signals:
    void Update_State();//发出状态改变信号
    void Exit();//发出退出信号，用来恢复主窗口焦点
};

//extern StoreWindow* wstore;
#endif // STOREWINDOW_H
