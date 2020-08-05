#ifndef MONSTERINFOLIST_H
#define MONSTERINFOLIST_H
#include <QListWidget>
#include <QPalette>
#include "monsterinfolistitem.h"
#include "variables.h"
#include <QString>
#include <QDebug>
#include <QTimer>


class MonsterInfoList : public QListWidget
{
     Q_OBJECT
public:
    explicit MonsterInfoList(QListWidget *parent = 0);
    void addItem();
    int Calculate_damage(MONSTER Monster);//在查看信息列表中计算和怪物对战伤害
    int return_Num;
    int display_num;

    MonsterInfoListItem* message_list_item[MONSTER_NUM];
    QListWidgetItem* newItem[MONSTER_NUM];

    QTimer* timer;


};


#endif // MONSTERINFOLIST_H
