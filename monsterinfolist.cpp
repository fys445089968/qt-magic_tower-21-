#include "monsterinfolist.h"

MonsterInfoList::MonsterInfoList(QListWidget *parent): QListWidget(parent)
{
    display_num =0;
    extern_timer = new QTimer(this);
    extern_timer->start();
    extern_timer->setInterval(600);

    setFocusPolicy(Qt::NoFocus); //去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //水平滚动条关闭
    //设置列表样式, QListWidget::item设置每一项
    this->setStyleSheet("QListWidget"
                        "{\
                        background:black;\
                        color:white;\
                        border:none;\
                        }\
                        QListWidget::item{\
                        border:none;\
                        height: 60px;\
                        }\
                        QScrollBar:vertical {\
                        background:transparent;\
                        width:9px;\
                        margin: 0px 0px 2px 0px;\
                        }\
                        QScrollBar::handle:vertical {\
                        background: rgb(195, 195, 195);\
                        min-height: 20px;\
                        border-radius: 3px;\
                        }\
                        QScrollBar::handle:vertical:hover{\
                        background:rgba(0,0,0,30%);\
                        }\
                        QScrollBar::add-line:vertical {\
                        height: 0px;\
                        subcontrol-position: bottom;\
                        subcontrol-origin: margin;\
                        }\
                        QScrollBar::sub-line:vertical {\
                        height: 0px;\
                        subcontrol-position: top;\
                        subcontrol-origin: margin;\
                        }");

}

int MonsterInfoList::Calculate_damage(MONSTER Monster)//计算怪物伤害
{
    int times;
    if(Braver.atk <= Monster.def)//勇士攻击力低于怪物防御值，无法攻击返回-1
        return -1;
    else//可以攻击
    {
        times = Monster.hp / (Braver.atk - Monster.def) ;//攻击次数
        if(Monster.atk <= Braver.def)//怪物打不动勇士，返回0
            return 0;
        else
        {
            return (Monster.atk - Braver.def) * times;//怪物打的动勇士，返回勇士掉血值
        }
    }
}

void MonsterInfoList::addItem()
{
    //逆序存放vtemp中的数字到temp中
    int temp[MONSTER_NUM];
    int k = static_cast<int>(vtemp.size()) - 1;
    for(int i =0;i < static_cast<int>(vtemp.size()) ;i ++)
    {
        temp[k] = vtemp[i];
        k --;
    }

    //message_list_item要以数组的形式建立，不然怪物没有动画效果
    for(int i =static_cast<int>(vtemp.size()) - 1;i >= 0  ;i --)
    {
        message_list_item[i] = new MonsterInfoListItem(); //创建一个自己定义的消息类
        message_list_item[i]->Init();
        message_list_item[i]->setFocusPolicy(Qt::NoFocus);
        message_list_item[i]->label_hp_val->setText(QString::number(Monster[temp[i]].hp));
        message_list_item[i]->label_name_val->setText(QString::fromStdWString(Monster[temp[i]].name));
        message_list_item[i]->label_atk_val->setText(QString::number(Monster[temp[i]].atk));
        message_list_item[i]->label_pdef_val->setText(QString::number(Monster[temp[i]].def));
        QString str = QString("%1·%2").arg(QString::number(Monster[temp[i]].gold)).arg(QString::number(Monster[temp[i]].exp));
        message_list_item[i]->label_exp_gold_val->setText(str);

        int return_num = Calculate_damage((Monster[temp[i]]));
        if(return_num == -1)//打不动，显示？？？？
            message_list_item[i]->label_damage_val->setText("????");
        else //打得动，显示掉血量
        {
            message_list_item[i]->label_damage_val->setText(QString::number(return_num));
        }

        //怪物头像
        QGraphicsScene *scene_m = new QGraphicsScene;
        scene_m->addPixmap(QPixmap::fromImage(Monster[temp[i]].img[0]));
        message_list_item[i]->head->setScene(scene_m);
        message_list_item[i]->head->show();
        message_list_item[i]->head->setStyleSheet("background:transparent;border:none;");

        //怪物头像
        QGraphicsScene *scene_m2 = new QGraphicsScene;
        scene_m2->addPixmap(QPixmap::fromImage(Monster[temp[i]].img[1]));
        message_list_item[i]->head_2->setScene(scene_m2);
        message_list_item[i]->head_2->hide();
        message_list_item[i]->head_2->setStyleSheet("background:transparent;border:none;");

        QListWidgetItem* newItem = new QListWidgetItem();
        this->insertItem(0, newItem);
        this->setItemWidget(newItem, message_list_item[i]); //在newItem这个项上显示message_list_item[i]这个窗口
        newItem->setHidden(false);
    }
    //这里connect放外面，如果在循环内会产生多个计时器导致不一致的错误。
    connect(extern_timer,&QTimer::timeout,this,[=](){
        display_num ++;
        if(display_num == 2)
            display_num = 0;
        if(display_num == 0)
        {
            for(int i =static_cast<int>(vtemp.size()) -1;i >= 0  ;i --)
            {
                message_list_item[i]->head->show();
                message_list_item[i]->head_2->hide();
            }
        }
        else if(display_num == 1)
        {
            for(int i =static_cast<int>(vtemp.size()) - 1;i >= 0  ;i --)
            {
                message_list_item[i]->head->hide();
                message_list_item[i]->head_2->show();
            }
        }
    });
}
