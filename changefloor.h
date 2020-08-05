#ifndef CHANGEFLOOR_H
#define CHANGEFLOOR_H

#include <QWidget>
#include "variables.h"
#include <QKeyEvent>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

namespace Ui {
class ChangeFloor;
}

class ChangeFloor : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeFloor(QWidget *parent = nullptr);
    void Init();
    int count;
    ~ChangeFloor();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::ChangeFloor *ui;
signals:
    void Select_Floor();//选中某层，准备跳楼
    void Exit();//退出选楼界面
};

#endif // CHANGEFLOOR_H
