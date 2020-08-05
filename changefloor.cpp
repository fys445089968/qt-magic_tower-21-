#include "changefloor.h"
#include "ui_changefloor.h"

ChangeFloor::ChangeFloor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeFloor)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    count = 1;
    Init();
}

void ChangeFloor::Init()
{
    this->setFocusPolicy(Qt::StrongFocus);

    ui->graphicsView->setStyleSheet("border:3px groove white;");//选中选项时背景有一个白色框提示。qlabel出现bug，窗口背景为黑色时，qlabel加边框不显示文字，所以用graphicsview做
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->move(10,95);
}

void ChangeFloor::keyPressEvent(QKeyEvent *event)
{
    //跳楼器
    if(event->key() == Qt::Key_Up  && Braver.Dialog_state_num == 11) //向上
    {
        count --;
        if(count == 0)
            count = 20;
        if(1 <= count && count <= 7)
            ui->graphicsView->move(10,95 + 40 * (count - 1));
        else if(7 < count && count <= 14)
            ui->graphicsView->move(125,95 + 40 * (count - 8));
        else if(14 < count && count <= 20)
            ui->graphicsView->move(240,95 + 40 * (count - 15));
    }

    if(event->key() == Qt::Key_Down  && Braver.Dialog_state_num == 11) //向下
    {
        count ++;
        if(count == 21)
            count = 1;
        if(1 <= count && count <= 7)
        {
            ui->graphicsView->move(10,95 + 40 * (count - 1));
        }
        else if(7 < count && count <= 14)
        {
            ui->graphicsView->move(125,95 + 40 * (count - 8));
        }

        else if(14 < count && count <= 20)
            ui->graphicsView->move(240,95 + 40 * (count - 15));

    }
    if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 11 )//空格键跳楼
    {
        if(Braver.whether_reach_floor[count] == true)
        {
            Braver.temp_floor = count;
            this->setFocusPolicy(Qt::NoFocus);
            emit Select_Floor();
        }
        else //不能飞音效
        {

        }

    }
    if(event->key() == Qt::Key_Escape && Braver.Dialog_state_num == 11 )//esc退出
    {
        this->setFocusPolicy(Qt::NoFocus);
        emit Exit();
    }
}

ChangeFloor::~ChangeFloor()
{
    delete ui;
}
