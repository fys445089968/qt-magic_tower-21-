#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include "variables.h"

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    void Init();
    int Count_Num;
    Ui::DialogWindow *ui;
    void Hide_Window();//隐藏窗口
    QTimer* space_timer;//space按钮提醒的渐变效果
    ~DialogWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QImage ImgFairy;
    QImage ImgBraver;
    QImage ImgThief;
    QImage ImgNpcOld;
    QImage ImgNpcRed;
    QImage ImgDevil16;
    QImage ImgDevil19;
    QImage ImgPrincess;
signals:
    void Exit();//发出退出信号，用来恢复主窗口焦点
    void Update_State();//状态改变信号
};

#endif // DIALOGWINDOW_H
