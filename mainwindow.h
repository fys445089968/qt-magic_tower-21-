#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QMediaPlayer>
#include <QSound>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <variables.h>
#include "storewindow.h"
#include "dialogwindow.h"
#include "monsterinfolist.h"
#include "monsterinfolistitem.h"
#include "changefloor.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void Before_Game_Scene();//游戏开始前画面
    void Update_pos();//更新Line_edit位置
    void InitGraphics();
    void LoadImageBeforeGame(); //初始化一些设置（如信号插槽等）
    void GameStart(); //游戏内容的初始化
    void ShowData();//展示勇士状态信息

    void ReGame();//重启游戏后初始化信息
    void Save_Game();//保存游戏
    void Load_Game();//读取游戏

    void Show_Monster_Data();//显示怪物信息
    void Change_Monster_Property(int num);//怪物属性改变,num表示第几次增强
    int Calculate(MONSTER Monster);//计算和怪物对战伤害
    void isalive();//判断当前楼层怪物是否存活

    void Hide_Before_Game_Scene();//隐藏游戏开始前画面
    void Hide_Game_Scene();//隐藏游戏界面
    void Show_Game_Scene();//显示游戏画面
    void Hide_Fight_Scene();//隐藏战斗界面
    void Show_Fight_Scene();//展示战斗界面
    void Handle_Fight();//战斗过程动画

    void ShowFloor(int k);//展示楼层信息
    void Handle_Key_Event(int key,int &x,int &y);//处理事件，如撞墙，杀怪，吃钥匙，开门等操作。key表示上下左右键，x，y为下一步位置
    void Sleep(int msec);//自定义延时函数
    void Gradual_Change_Animation();//渐变动画
    void Open_Door_Animation(int p_x,int p_y);//开门动画

    QTimer* Fight_timer;//战斗定时器
    QTimer* Text_timer;//文本移动计时器
    QTimer* Normal_timer;//普通计时器，刷新屏幕用，让怪物一动一动的
    QTimer* Open_Door_timer;//开门定时器，开门动画用
    QTimer* start_space_timer;//开始界面文字的space渐变效果实现
    QTimer* Braver_timer;//勇士走路动画间隔

    QGraphicsScene *scene_floor;//当前楼层内容显示
    QGraphicsPixmapItem** pixs;//为楼层一项一项添加内容

    QGraphicsOpacityEffect* m_pGraphicsOpacityEffect;//渐变动画
    QPropertyAnimation* m_pNameAnimation;//动画效果

    QMediaPlayer* bgm;//背景音乐

    StoreWindow* storewindow;//商店窗口
    DialogWindow* dialogwindow;//对话框窗口
    ChangeFloor* changefloorwindow;//飞行器窗口

    int display_it;//0显示第一张图，1显示第二张图，用于地图怪物动态效果
    int open_door_num;//开门动画用
    int L_Num ;//L键按下次数
    int keyUpCnt; //按键松开的时间
    int Current_Floor_Num;//当前所在层数
    //int floor_array[11][11];//地板对应图片
    int Monster_temp_num;//战斗时怪物序号
    int Braver_temp_hp;//勇士临时血量存数据用
    int door_x;//临时存储门位置x
    int door_y;//临时存储门位置y
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QImage img_background;
    QImage ImgWall;
    QImage ImgUpstairs;
    QImage ImgDownstairs;
    QImage ImgFloor;
    QImage ImgInfo;
    QImage ImgYDoor[4];
    QImage ImgBDoor[4];
    QImage ImgRDoor[4];
    QImage ImgGDoor[4];
    QImage ImgIDoor[4];
    QImage ImgFalseWall[4];
    QImage ImgBraver[4][2];
    QImage ImgStoreLeft;
    QImage ImgStoreMiddle[4];
    QImage ImgStoreRight;
    QImage ImgYKey;
    QImage ImgBKey;
    QImage ImgRKey;
    QImage ImgBigYKey;
    QImage ImgBottle1;
    QImage ImgBottle2;
    QImage ImgRGem;
    QImage ImgBGem;
    QImage ImgSLevelUp;
    QImage ImgBLevelUp;
    QImage ImgHolyWater;
    QImage ImgHammer;
    QImage ImgBigGold;
    QImage ImgCross;
    QImage ImgChangeFloor;
    QImage ImgMagicWand[2];
    QImage ImgSword[3];
    QImage ImgShield[3];
    QImage ImgNpcOld[2];
    QImage ImgNpcRed[2];
    QImage ImgNpcFairy[2];
    QImage ImgNpcThief[2];
    QImage ImgNpcprincess[2];
    QImage ImgGalaxy[2];
    QImage ImgMagma[2];
    int Floor[11][11];
    QVector<QImage>ImgMonster;

signals:
    void UpDownstair_Animation();//上下楼转场动画信号发出
    void Fight_End();




};

#endif // MAINWINDOW_H
