#include "storewindow.h"
#include "ui_storewindow.h"

//StoreWindow* wstore;

StoreWindow::StoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    count = 1;
    Init();
    Braver.Whether_Press = false;
}

void StoreWindow::Init()
{
    this->ui->graphicsView->hide();
    this->ui->graphicsView_old->hide();
    this->ui->graphicsView_red->hide();
    //3楼商店
    if(Braver.Dialog_state_num == 8)
    {
        this->ui->graphicsView->show();
    }
    //5楼经验商店
    else if(Braver.Dialog_state_num == 6)
    {
        this->ui->graphicsView_old->show();
        this->ui->label->setText("你好，英雄的人类，只");
        this->ui->label_2->setText("要你有足够的经验，我就");
        this->ui->label_3->setText("可以让你变得更强大");
        this->ui->label_4->setText("提升一级（需要100点）");
        this->ui->label_5->setText("增加攻击5（需要30点）");
        this->ui->label_6->setText("增加防御5（需要30点）");
    }
    //5楼钥匙商店
    else if(Braver.Dialog_state_num == 7)
    {
        this->ui->graphicsView_red->show();
        this->ui->label->setText(" 相信你一定有特殊的需");
        this->ui->label_2->setText("要，只要你有金币，我就");
        this->ui->label_3->setText("可以帮你");
        this->ui->label_4->setText("购买1把黄钥匙（$ 10）");
        this->ui->label_5->setText("购买1把蓝钥匙（$ 50）");
        this->ui->label_6->setText("购买1把红钥匙（$ 100）");
    }
    //11楼金币商店
    else if(Braver.Dialog_state_num == 10)
    {
        this->ui->graphicsView->show();
        this->ui->label->setText(" 想要增加你的能力吗？");
        this->ui->label_2->setText("如果你有 100 个金币，");
        this->ui->label_3->setText("你可以任意选择一项：");
        this->ui->label_4->setText("增加 4000 点生命");
        this->ui->label_5->setText("增加 20 点攻击");
        this->ui->label_6->setText("增加 20 点防御");
    }
    //12楼钥匙商店
    else if(Braver.Dialog_state_num == 12)
    {
        this->ui->graphicsView_red->show();
        this->ui->label->setText(" 相信你一定有特殊的需");
        this->ui->label_2->setText("要，我这里大量回收钥匙");
        this->ui->label_3->setText(" ");
        this->ui->label_4->setText("出售1把黄钥匙（$ 7）");
        this->ui->label_5->setText("出售1把蓝钥匙（$ 35）");
        this->ui->label_6->setText("出售1把红钥匙（$ 70）");
    }
    //13楼经验商店
    else if(Braver.Dialog_state_num == 13)
    {
        this->ui->graphicsView_old->show();
        this->ui->label->setText("你好，英雄的人类，只");
        this->ui->label_2->setText("要你有足够的经验，我就");
        this->ui->label_3->setText("可以让你变得更强大");
        this->ui->label_4->setText("提升三级（需要270点）");
        this->ui->label_5->setText("增加攻击17（需要95点）");
        this->ui->label_6->setText("增加防御17（需要95点）");
    }

    this->setFocusPolicy(Qt::StrongFocus);

    ui->graphicsView_2->setStyleSheet("border:3px groove white;");//选中选项时背景有一个白色框提示。qlabel出现bug，窗口背景为黑色时，qlabel加边框不显示文字，所以用graphicsview做
    ui->graphicsView_2->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView_2->move(35,125);

    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->label_2->setFocusPolicy(Qt::NoFocus);
    ui->label_3->setFocusPolicy(Qt::NoFocus);
    ui->label_4->setFocusPolicy(Qt::NoFocus);
    ui->label_5->setFocusPolicy(Qt::NoFocus);
    ui->label_6->setFocusPolicy(Qt::NoFocus);

    ImgStoreMiddle = QImage(":/Graphics/Characters/001-npc02.png").copy(32 , 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgNpcOld = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgNpcRed = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );

    //设置商店头像图片
    QGraphicsScene *scene_store = new QGraphicsScene;
   // scene_store->setBackgroundBrush(QPixmap::fromImage(ImgStoreMiddle));
    QGraphicsPixmapItem* pix_monster = new QGraphicsPixmapItem();
    pix_monster->setPixmap(QPixmap::fromImage(ImgStoreMiddle));
    pix_monster->setPos(QPointF(0,0));
    scene_store->addItem(pix_monster);
    this->ui->graphicsView->setScene(scene_store);

    //老头头像
    QGraphicsScene *scene_old = new QGraphicsScene;
    scene_old->addPixmap(QPixmap::fromImage(ImgNpcOld));
    this->ui->graphicsView_old->setScene(scene_old);
    this->ui->graphicsView_old->setStyleSheet("background:transparent;border:none;");

    //商人头像
    QGraphicsScene *scene_red = new QGraphicsScene;
    scene_red->addPixmap(QPixmap::fromImage(ImgNpcRed));
    this->ui->graphicsView_red->setScene(scene_red);
    //this->ui->graphicsView_braver->show();
    this->ui->graphicsView_red->setStyleSheet("background:transparent;border:none;");

}

void StoreWindow::keyPressEvent(QKeyEvent *event)
{
    //3楼商店
    if(Braver.Dialog_state_num == 8)
    {
        if(event->key() == Qt::Key_Up  && count > 1) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4 ) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.gold >= 25)
            {
                Braver.gold -= 25;
                Braver.hp += 800;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.gold >= 25)
            {
                Braver.gold -= 25;
                Braver.atk += 4;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.gold >= 25)
            {
                Braver.gold -= 25;
                Braver.def += 4;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }

    //5楼经验商店
    else if(Braver.Dialog_state_num == 6)
    {
        if(event->key() == Qt::Key_Up  && count > 1 ) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4 ) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space  )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.exp >= 100)
            {
                Braver.level += 1;
                Braver.exp -= 100;
                Braver.hp += 1000;
                Braver.atk += 7;
                Braver.def += 7;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.exp >= 30)
            {
                Braver.exp -= 30;
                Braver.atk += 5;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.exp >= 30)
            {
                Braver.exp -= 30;
                Braver.def += 5;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }

    //5楼钥匙商店
    else if(Braver.Dialog_state_num == 7)
    {
        if(event->key() == Qt::Key_Up  && count > 1) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.gold >= 10)
            {
                Braver.gold -= 10;
                Braver.key1 += 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.gold >= 50)
            {
                Braver.gold -= 50;
                Braver.key2 += 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.exp >= 100)
            {
                Braver.gold -= 100;
                Braver.key3 += 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }

    //11楼商店
    else if ( Braver.Dialog_state_num == 10)
    {
        if(event->key() == Qt::Key_Up  && count > 1) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4 ) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.gold >= 100)
            {
                Braver.gold -= 100;
                Braver.hp += 4000;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.gold >= 100)
            {
                Braver.gold -= 100;
                Braver.atk += 20;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.gold >= 100)
            {
                Braver.gold -= 100;
                Braver.def += 20;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }

    //12楼钥匙商店
    else if(Braver.Dialog_state_num == 12)
    {
        if(event->key() == Qt::Key_Up  && count > 1) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.key1 >= 1)
            {
                Braver.gold += 7;
                Braver.key1 -= 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.key2 >= 1)
            {
                Braver.gold += 35;
                Braver.key2 -= 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.key3 >= 1)
            {
                Braver.gold += 70;
                Braver.key3 -= 1;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }

    //13楼经验商店
    else if(Braver.Dialog_state_num == 13)
    {
        if(event->key() == Qt::Key_Up  && count > 1) //向上
        {
            count --;
            if(count == 1)
                ui->graphicsView_2->move(35,125);
            else if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
        }

        if(event->key() == Qt::Key_Down  && count < 4 ) //向下
        {
            count ++;
            if(count == 2)
                ui->graphicsView_2->move(35,185);
            else if(count == 3)
                ui->graphicsView_2->move(35,245);
            else if(count == 4)
                ui->graphicsView_2->move(35,305);
        }
        if(event->key() == Qt::Key_Space )//空格键购买
        {
            if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->hide();
            }
            if(count == 1 && Braver.exp >= 270)
            {
                Braver.level += 3;
                Braver.exp -= 270;
                Braver.hp += 3000;
                Braver.atk += 21;
                Braver.def += 21;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 2 && Braver.exp >= 95)
            {
                Braver.exp -= 95;
                Braver.atk += 17;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 3 && Braver.exp >= 95)
            {
                Braver.exp -= 95;
                Braver.def += 17;
                emit Update_State();//发出状态改变信号
            }
            else if(count == 4)
            {
                Braver.Whether_Press = true;
                emit Exit();//退出信号，恢复主窗口焦点
                this->close();
            }
        }
    }
}

StoreWindow::~StoreWindow()
{
    delete ui;
}


