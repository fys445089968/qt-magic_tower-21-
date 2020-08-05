#ifndef MONSTERINFOLISTITEM_H
#define MONSTERINFOLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>

class MonsterInfoListItem : public QWidget
{
    Q_OBJECT
public:
    explicit MonsterInfoListItem(QWidget *parent = nullptr);
    QGraphicsView* head;
    QGraphicsView* head_2;
    QLabel* label_name;
    QLabel* label_hp;
    QLabel* label_atk;
    QLabel* label_pdef;
    QLabel* label_exp_gold;
    QLabel* label_damage;
    QLabel* label_name_val;
    QLabel* label_hp_val;
    QLabel* label_atk_val;
    QLabel* label_pdef_val;
    QLabel* label_exp_gold_val;
    QLabel* label_damage_val;
    void Init();

signals:

public slots:
};




#endif // MONSTERINFOLISTITEM_H
