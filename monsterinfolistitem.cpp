#include "monsterinfolistitem.h"

MonsterInfoListItem::MonsterInfoListItem(QWidget *parent) : QWidget(parent)
{

}
void MonsterInfoListItem::Init()
{
    //初始化
    head = new QGraphicsView(this);
    head_2 = new QGraphicsView(this);
    label_name = new QLabel(this);
    label_hp = new QLabel(this);
    label_atk = new QLabel(this);
    label_pdef = new QLabel(this);
    label_exp_gold = new QLabel(this);
    label_damage = new QLabel(this);
    label_name_val = new QLabel(this);
    label_hp_val = new QLabel(this);
    label_atk_val = new QLabel(this);
    label_pdef_val = new QLabel(this);
    label_exp_gold_val = new QLabel(this);
    label_damage_val = new QLabel(this);

    //设置颜色，对齐方式
    label_name->setStyleSheet("color:#cccccc;");
    label_name->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_name->setFixedSize(55, 20);
    label_name->setText(QString::fromStdWString(L"名称"));
    label_hp->setStyleSheet("color:#cccccc;");
    label_hp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_hp->setFixedSize(55, 20);
    label_hp->setText(QString::fromStdWString(L"生命"));
    label_atk->setStyleSheet("color:#cccccc;");
    label_atk->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_atk->setFixedSize(55, 20);
    label_atk->setText(QString::fromStdWString(L"攻击"));
    label_pdef->setStyleSheet("color:#cccccc;");
    label_pdef->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_pdef->setFixedSize(55, 20);
    label_pdef->setText(QString::fromStdWString(L"防御"));
    label_exp_gold->setStyleSheet("color:#cccccc;");
    label_exp_gold->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_exp_gold->setFixedSize(96, 20);
    label_exp_gold->setText(QString::fromStdWString(L"金·经"));
    label_damage->setStyleSheet("color:#cccccc;");
    label_damage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_damage->setFixedSize(96, 20);
    label_damage->setText(QString::fromStdWString(L"损失"));
    label_name_val->setStyleSheet("color:#ffffff;");
    label_name_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_name_val->setFixedSize(96, 20);
    label_hp_val->setStyleSheet("color:#ffffff;");
    label_hp_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_hp_val->setFixedSize(96, 20);
    label_atk_val->setStyleSheet("color:#ffffff;");
    label_atk_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_atk_val->setFixedSize(55, 20);
    label_pdef_val->setStyleSheet("color:#ffffff;");
    label_pdef_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_pdef_val->setFixedSize(55, 20);
    label_exp_gold_val->setStyleSheet("color:#ffffff;");
    label_exp_gold_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_exp_gold_val->setFixedSize(55, 20);
    label_damage_val->setStyleSheet("color:#ffffff;");
    label_damage_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_damage_val->setFixedSize(55, 20);

    //设置头像大小
    head->setFixedSize(48,48);

    //布局
    head->move(10,10);
    head_2->move(10,10);
    label_name->move(68,10);
    label_name_val->move(133, 10);
    label_hp->move(68, 35);
    label_atk->move(239, 10);
    label_pdef->move(239, 35);
    label_hp_val->move(133, 35);
    label_atk_val->move(314, 10);
    label_pdef_val->move(314, 35);
    label_exp_gold->move(354, 10);
    label_damage->move(354, 35);
    label_exp_gold_val->move(450, 10);
    label_damage_val->move(450, 35);

    setFocusPolicy(Qt::NoFocus);

    //加载事件过滤器
    head->installEventFilter(this);
}
