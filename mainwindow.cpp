#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QGraphicsScene>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include "variables.h"
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Current_Floor_Num = CURRENT_FLOOR_NUM;//Floor是map容器，第零层（序章层）对应Floor[1]，所以Current_Floor_Num比现实层数大1.
    L_Num = 0;//L键按下次数，方便再次按L退出怪物信息界面
    display_it = 0;//显示不同图片，怪物动态效果用
    open_door_num = 0;//开门动画计数用
    keyUpCnt = 100;//用来使勇士移动时才有动画，不动时静止

    scene_floor = new QGraphicsScene;//地板色
    pixs = new QGraphicsPixmapItem*[121];//建立PixmapItem数组，返回pixs指针

    QSound* bgm = new QSound(":/Graphics/bgm.wav",this);
    bgm->setLoops(-1);//背景音乐循环播放
    bgm->play();

    ui->graphicsView_7->setFocusPolicy(Qt::NoFocus);

    Gradual_Change_Animation();//上下楼渐变动画
}

void MainWindow::Before_Game_Scene()//游戏开始前画面
{

    //隐藏游戏界面和战斗界面
    Hide_Game_Scene();
    Hide_Fight_Scene();
    this->ui->textBrowser->hide();
    this->ui->textEdit->hide();

    //文本滚动计时器
    Text_timer = new QTimer;
    //单击开始游戏进入textEdit文本
    connect(this->ui->pushButton,&QPushButton::clicked,this,[=](){
        Hide_Before_Game_Scene();
        this->ui->textBrowser->show();
        this->ui->textEdit->show();
        Text_timer->start();
        Text_timer->setInterval(TEXT_INTERVAL);

        //按空格跳出文本
        int k =0;
        int count =0;
        start_space_timer = new QTimer(this);
        start_space_timer->start();
        start_space_timer->setInterval(400);
        connect(start_space_timer,&QTimer::timeout,this,[=]()mutable{
            count++;
            if(count % 2 ==0)
                k =255;
            else
                k = 75;
            ui->textBrowser->setTextColor(QColor(255,255,255,k));
            ui->textBrowser->setText("--space--");
        });

        //文本向上滚动播放
        connect(Text_timer,&QTimer::timeout,this,[=](){
            Update_pos();//实时更新文本位置
        });
    });
}

void MainWindow::Update_pos()//更新textEdit的y坐标位置，让其上移
{
    static int height = 1;
    this->ui->textEdit->move(110,this->height() - height);
    height += 1;
    if(ui->textEdit->pos().y() <= -300)
    {
        this->ui->graphicsView_7->hide();
        this->ui->textEdit->hide();
        Show_Game_Scene();
        Text_timer->stop();
    }

}

void MainWindow::GameStart()
{
    //完整游戏不要注释这两行代码
    Before_Game_Scene();
    Show_Game_Scene();

    //直接进入游戏画面，测试用
   // Hide_Before_Game_Scene();
    //Show_Game_Scene();
    this->ui->textBrowser->hide();
    //this->ui->graphicsView_7->hide();//。。。。。

    init_monsters();//存放怪物数据初始化

    LoadImageBeforeGame();//加载游戏图片

    InitGraphics();//初始化游戏窗口图片

    ShowData();//勇士数据
}

void MainWindow::LoadImageBeforeGame()//初始化游戏图片
{
    img_background = QImage(":/Graphics/Tilesets/Mota.png").copy(160, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgWall = QImage(":/Graphics/Tilesets/Mota.png").copy(192, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgUpstairs = QImage(":/Graphics/Tilesets/Mota.png").copy(32, 992, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgDownstairs = QImage(":/Graphics/Tilesets/Mota.png").copy(0, 992, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgFloor = QImage(":/Graphics/Tilesets/Mota.png").copy(96, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgInfo = QImage(":/Graphics/Characters/item02.png").copy(64, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgYKey = QImage(":/Graphics/Characters/item01.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBKey = QImage(":/Graphics/Characters/item01.png").copy(32, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgRKey = QImage(":/Graphics/Characters/item01.png").copy(64, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBigYKey = QImage(":/Graphics/Characters/item01.png").copy(64, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBottle1 = QImage(":/Graphics/Characters/item03.png").copy(0, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBottle2 = QImage(":/Graphics/Characters/item03.png").copy(32, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgRGem = QImage(":/Graphics/Characters/item03.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBGem = QImage(":/Graphics/Characters/item03.png").copy(32, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgSLevelUp = QImage(":/Graphics/Characters/item02.png").copy(0, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBLevelUp = QImage(":/Graphics/Characters/item02.png").copy(64, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgHammer =  QImage(":/Graphics/Characters/item02.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgHolyWater = QImage(":/Graphics/Characters/item03.png").copy(96, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBigGold = QImage(":/Graphics/Characters/item01.png").copy(96, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgCross = QImage(":/Graphics/Characters/item02.png").copy(96, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgSword[0] = QImage(":/Graphics/Characters/item04.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgSword[1] = QImage(":/Graphics/Characters/item04.png").copy(32, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgSword[2] = QImage(":/Graphics/Characters/item04.png").copy(0, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgShield[0] = QImage(":/Graphics/Characters/item04.png").copy(0, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgShield[1] = QImage(":/Graphics/Characters/item04.png").copy(64, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgShield[2] = QImage(":/Graphics/Characters/item04.png").copy(0, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgStoreLeft = QImage(":/Graphics/Tilesets/Mota.png").copy(96, 992, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgStoreRight = QImage(":/Graphics/Tilesets/Mota.png").copy(160, 992, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgChangeFloor = QImage(":/Graphics/Characters/item02.png").copy(64, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgMagicWand[0] = QImage(":/Graphics/Characters/item05.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgMagicWand[1] = QImage(":/Graphics/Characters/item05.png").copy(32, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    for (int t = 0; t <= 3; t++)
        ImgStoreMiddle[t] = QImage(":/Graphics/Characters/001-npc02.png").copy(32 * t, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    for (int t = 0; t <= 3; t++)
    {
        ImgYDoor[t] = QImage(":/Graphics/Characters/men001.png").copy(0, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgBDoor[t] = QImage(":/Graphics/Characters/men001.png").copy(32, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgRDoor[t] = QImage(":/Graphics/Characters/men001.png").copy(64, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgGDoor[t] = QImage(":/Graphics/Characters/men001.png").copy(96, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgIDoor[t] = QImage(":/Graphics/Characters/men002.png").copy(96, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgFalseWall[t] = QImage(":/Graphics/Characters/men002.png").copy(32, 32 * t, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    }
    for (int t = 0; t < 2; t++)
    {
        ImgNpcOld[t] = QImage(":/Graphics/Characters/001-npc01.png").copy(64 * t, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgNpcRed[t] = QImage(":/Graphics/Characters/001-npc01.png").copy(64 * t, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgNpcFairy[t] = QImage(":/Graphics/Characters/001-npc01.png").copy(64 * t, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgNpcThief[t] = QImage(":/Graphics/Characters/001-npc01.png").copy(64 * t, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgMagma[t] = QImage(":/Graphics/Autotiles/100-CF_Lava01.png").copy(64 * t, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgGalaxy[t] = QImage(":/Graphics/Autotiles/100-CF_Lava02.png").copy(64 * t, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgNpcprincess[t] = QImage(":/Graphics/Characters/001-npc02.png").copy(64 * t, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    }
    for (int t = 0; t <= 3; t++)
    {
        ImgBraver[t][0] = QImage(IMG_BRAVE_PATH).copy(0, t * 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
        ImgBraver[t][1] = QImage(IMG_BRAVE_PATH).copy(32, t * 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    }
}

void MainWindow::InitGraphics()//初始化游戏窗口窗口图片
{
    //窗口大小为固定值，不可以更改
    this->setFixedSize(864,600);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();//一进游戏不用单击获取焦点就可以键盘操作

    //首先画背景。背景为深蓝色砖块
    QPalette palette;
    palette.setBrush(QPalette::Window, QPixmap::fromImage(img_background));
    this->setPalette(palette);

    //设置graphicsView背景颜色
    QGraphicsScene *scene_llayer = new QGraphicsScene;
    scene_llayer->setBackgroundBrush(QPixmap::fromImage(ImgFloor));
    this->ui->graphicsView->setScene(scene_llayer);
    this->ui->graphicsView_3->setScene(scene_llayer);
    this->ui->graphicsView_4->setScene(scene_llayer);
    this->ui->graphicsView_5->setScene(scene_llayer);
    this->ui->graphicsView_6->setScene(scene_llayer);

    //水平滚动条关闭
    this->ui->graphicsView_6->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //勇士图标
    this->ui->label_Icon->setPixmap(QPixmap::fromImage(ImgBraver[0][0]));
    this->ui->label_Icon->setFixedSize(60,60);

    //黄钥匙图标
    this->ui->label_YKey->setPixmap(QPixmap::fromImage(ImgYKey));
    this->ui->label_YKey->setFixedSize(45,45);

    //蓝钥匙图标
    this->ui->label_BKey->setPixmap(QPixmap::fromImage(ImgBKey));
    this->ui->label_BKey->setFixedSize(45,45);

    //红钥匙图标
    this->ui->label_RKey->setPixmap(QPixmap::fromImage(ImgRKey));
    this->ui->label_RKey->setFixedSize(45,45);

    //显示楼层
    if(Current_Floor_Num == 24 || Current_Floor_Num == 25 || Current_Floor_Num == 26)
    {
        QString str = QString("第 23 层");
        this->ui->label_4->setText(str);
    }
    if(Current_Floor_Num == 27 || Current_Floor_Num == 28)
    {
        QString str = QString("第 24 层");
        this->ui->label_4->setText(str);
    }
    if(Current_Floor_Num != 28 && Current_Floor_Num != 24 && Current_Floor_Num != 25 && Current_Floor_Num != 26 && Current_Floor_Num != 27)
    {
        //显示第几层
        QString str = QString("第 %1 层").arg(Current_Floor_Num - 1);
        this->ui->label_4->setText(str);
    }
    this->ui->label_save->setText("S b保存");
    this->ui->listWidget->hide();
    Hide_Fight_Scene();

    //初始化战斗定时器
    Fight_timer = new QTimer(this);
    connect(Fight_timer,&QTimer::timeout,this,[=](){
        Handle_Fight();
    });

    //初始化普通定时器，让怪物有动态效果
    Normal_timer = new QTimer(this);
    Normal_timer->start();
    Normal_timer->setInterval(400);
    connect(Normal_timer,&QTimer::timeout,this,[=](){
        display_it ++;
        if(display_it == 2)
            display_it = 0;
        ShowFloor(Current_Floor_Num);
    });

    //勇士走路动画计时器（走路动画和怪物动画间隔时间不同）
    Braver_timer = new QTimer(this);
    Braver_timer->start();
    Braver_timer->setInterval(200);
    connect(Braver_timer,&QTimer::timeout,this,[=](){
        keyUpCnt += 1;
        ShowFloor(Current_Floor_Num);
    });
}

void MainWindow::ShowData()//展示勇士状态
{
    this->ui->label_health->setStyleSheet("color:white;");//使用样式表
    this->ui->label_health_value->setText(QString::number(Braver.hp));
    this->ui->label_health_value->setStyleSheet("color:white;");
    this->ui->label_attack->setStyleSheet("color:white;");
    this->ui->label_attack_value->setStyleSheet("color:white;");
    this->ui->label_attack_value->setText(QString::number(Braver.atk));
    this->ui->label_defence->setStyleSheet("color:white;");
    this->ui->label_defence_value->setStyleSheet("color:white;");
    this->ui->label_defence_value->setText(QString::number(Braver.def));
    this->ui->label_gold->setStyleSheet("color:white;");
    this->ui->label_gold_value->setStyleSheet("color:white;");
    this->ui->label_gold_value->setText(QString::number(Braver.gold));
    this->ui->label_exp->setStyleSheet("color:white;");
    this->ui->label_exp_value->setStyleSheet("color:white;");
    this->ui->label_exp_value->setText(QString::number(Braver.exp));
    this->ui->label_Y_Num->setStyleSheet("color:white;");
    this->ui->label_Y_Num->setText(QString::number(Braver.key1));
    this->ui->label_B_Num->setStyleSheet("color:white;");
    this->ui->label_B_Num->setText(QString::number(Braver.key2));
    this->ui->label_R_Num->setStyleSheet("color:white;");
    this->ui->label_R_Num->setText(QString::number(Braver.key3));
    this->ui->label_4->setStyleSheet("color:white;");
    this->ui->label_12->setStyleSheet("color:white;");
    this->ui->label_12->setText(QString::number( Braver.level));
    this->ui->label_13->setStyleSheet("color:white;");
    this->ui->label_save->setStyleSheet("color:white;");
    this->ui->label_quit->setStyleSheet("color:white;");
    this->ui->label_access->setStyleSheet("color:white;");
    this->ui->label_restart->setStyleSheet("color:white;");
}

void MainWindow::ReGame()//重新加载游戏
{
    //初始化勇士数据
    Braver.status = 0;
    Braver.level = INIT_LEVEL;
    Braver.hp = INIT_HP;
    Braver.atk = INIT_ATK;
    Braver.def = INIT_DEF;
    Braver.pos_x = 9;
    Braver.pos_y = 5;
    Braver.floor = 0;
    Braver.exp = INIT_EXP;
    Braver.gold = INIT_GOLD;
    Braver.key1 = INIT_YKEY;
    Braver.key2 = INIT_BKEY;
    Braver.key3 = INIT_RKEY;
    Braver.face = 0;//0向下走，露脸；1左；2右；3向上走，漏背部
    Braver.temp_floor = 0;
    Braver.Dialog_state_num = 0;
    Braver.Whether_Press = true;
    Braver.Has_Change_Floor = false;
    Braver.Has_Cross = false;
    Braver.Summit_Cross = false;
    Braver.Has_Info = false;
    Braver.Speak_Fairy = false;
    Braver.Speak_Fairy22 = false;
    Braver.Has_Hammer = false;
    Braver.Speak_Thief = false;
    Braver.Speak_old16 = false;
    Braver.Speak_fairy_afterold = false;
    Braver.Speak_Devils16 = false;
    Braver.Speak_Devils19 = false;
    Braver.Speak_Devils21 = false;
    Braver.whether_get_magic_wand[0] = false;
    Braver.whether_get_magic_wand[1] = false;
    Braver.whether_reach_floor17 = false;
    Braver.whether_summit_magic_wand = false;
    Braver.whether_open_flourdoor = false;
    for(int i =0;i < 3;i++)
        Braver.whether_improve_monster_property[i] = false;
    for(int i =0;i < FLOOR_NUM;i++)
        Braver.whether_reach_floor[i] = true;
    Braver.Dialog_state_num = 9;
    Current_Floor_Num = 1;
    for(int k =0; k < 8;k ++)
    {
        for(int i =0; i < 11; i++)
        {
            for(int j =0; j < 11; j++)
            {
                floor.Floor[k+1][i][j] = floor.floor_array[k][i][j];
            }
        }
    }

    ui->listWidget->hide();
    ShowData();
    ShowFloor(1);
}

void MainWindow::Save_Game()//保存游戏
{  
    //将各项数据存储起来
    Braver.save_hp = Braver.hp;
    Braver.save_atk = Braver.atk;
    Braver.save_def = Braver.def;
    Braver.save_exp = Braver.exp;
    Braver.save_gold = Braver.gold;
    Braver.save_key1 = Braver.key1;
    Braver.save_key2 = Braver.key2;
    Braver.save_key3 = Braver.key3;
    Braver.save_level = Braver.level;
    Braver.save_pos_x = Braver.pos_x;
    Braver.save_pos_y = Braver.pos_y;
    Braver.save_Has_Info = Braver.Has_Info;
    Braver.save_Has_Cross = Braver.Has_Cross;
    Braver.save_Summit_Cross = Braver.Summit_Cross;
    Braver.save_Speak_Fairy = Braver.Speak_Fairy;
    Braver.save_Speak_Fairy22 = Braver.Speak_Fairy22;
    Braver.save_Speak_fairy_afterold = Braver.Speak_fairy_afterold;
    Braver.save_Speak_old16 = Braver.Speak_old16;
    Braver.save_Speak_Thief = Braver.Speak_Thief;
    Braver.save_Speak_Devils16 = Braver.Speak_Devils16;
    Braver.save_Speak_Devils19 = Braver.Speak_Devils19;
    Braver.save_Speak_Devils21 = Braver.Speak_Devils21;
    Braver.save_whether_reach_floor17 = Braver.whether_reach_floor17;
    Braver.save_whether_open_flourdoor = Braver.whether_open_flourdoor;
    Braver.save_whether_summit_magic_wand = Braver.whether_summit_magic_wand;
    Braver.save_Dialog_state_num = Braver.Dialog_state_num;
    Braver.save_floor_num = Current_Floor_Num;
    Braver.save_temp_floor = Braver.temp_floor;
    Braver.save_Has_Hammer = Braver.Has_Hammer;
    Braver.save_Has_Change_Floor = Braver.Has_Change_Floor;
    for(int i = 0; i< 2;i++)
    {
        Braver.save_whether_get_magic_wand[i] = Braver.whether_get_magic_wand[i];
    }
    for(int i = 0; i< FLOOR_NUM;i++)
    {
        Braver.save_whether_reach_floor[i] = Braver.whether_reach_floor[i];
    }
    for(int i = 0; i< 3;i++)
    {
        Braver.save_whether_improve_monster_property[i] = Braver.whether_improve_monster_property[i];
    }

    //将地图信息暂存
    for(int k =0; k < 8;k ++)
    {
        for(int i =0; i < 11; i++)
        {
            for(int j =0; j < 11; j++)
            {
                floor.floor_save[k][i][j] = floor.Floor[k+1][i][j];
            }
        }
    }
}

void MainWindow::Load_Game()//读取游戏
{
    Braver.hp = Braver.save_hp;
    Braver.atk = Braver.save_atk;
    Braver.def = Braver.save_def;
    Braver.exp = Braver.save_exp;
    Braver.gold = Braver.save_gold;
    Braver.key1 = Braver.save_key1;
    Braver.key2 = Braver.save_key2;
    Braver.key3 = Braver.save_key3;
    Braver.level = Braver.save_level;
    Braver.pos_x = Braver.save_pos_x;
    Braver.pos_y = Braver.save_pos_y;
    Braver.Has_Info = Braver.save_Has_Info;
    Braver.Has_Cross = Braver.save_Has_Cross;
    Braver.Summit_Cross = Braver.save_Summit_Cross;
    Braver.Speak_Fairy = Braver.save_Speak_Fairy;
    Braver.Speak_Fairy22 = Braver.save_Speak_Fairy22;
    Braver.Speak_fairy_afterold = Braver.save_Speak_fairy_afterold;
    Braver.Speak_old16 = Braver.save_Speak_old16;
    Braver.Speak_Thief = Braver.save_Speak_Thief;
    Braver.Speak_Devils16 = Braver.save_Speak_Devils16;
    Braver.Speak_Devils19 = Braver.save_Speak_Devils19;
    Braver.Speak_Devils21 = Braver.save_Speak_Devils21;
    Braver.whether_reach_floor17 = Braver.save_whether_reach_floor17;
    Braver.whether_open_flourdoor = Braver.save_whether_open_flourdoor;
    Braver.whether_summit_magic_wand = Braver.save_whether_summit_magic_wand;
    Braver.Dialog_state_num = Braver.save_Dialog_state_num;
    Braver.temp_floor = Braver.save_temp_floor;
    Braver.Has_Hammer = Braver.save_Has_Hammer;
    Braver.Has_Change_Floor = Braver.save_Has_Change_Floor;
    for(int i = 0; i< 2;i++)
    {
        Braver.whether_get_magic_wand[i] = Braver.save_whether_get_magic_wand[i];
    }
    for(int i = 0; i< FLOOR_NUM;i++)
    {
        Braver.whether_reach_floor[i] = Braver.save_whether_reach_floor[i];
    }
    for(int i = 0; i< 3;i++)
    {
        Braver.whether_improve_monster_property[i] = Braver.save_whether_improve_monster_property[i];
    }
    for(int k =0; k < 8;k ++)
    {
        for(int i =0; i < 11; i++)
        {
            for(int j =0; j < 11; j++)
            {
                floor.Floor[k+1][i][j] = floor.floor_save[k][i][j];
            }
        }
    }

}

void MainWindow::Change_Monster_Property(int num)//怪物属性提升
{
    if(num == 1)//第一次增强，去过17层
    {
        Monster[25].name = L"灵法师";
        Monster[25].hp = 2000;
        Monster[25].atk = 1106;
        Monster[25].def = 973;
        Monster[25].boss = false;
        Monster[25].attrib = 0;
        Monster[25].gold = 106;
        Monster[25].exp = 93;

        Monster[26].name = L"灵武士";
        Monster[26].hp = 1600;
        Monster[26].atk = 1306;
        Monster[26].def = 1200;
        Monster[26].boss = false;
        Monster[26].attrib = 0;
        Monster[26].gold = 117;
        Monster[26].exp = 100;

        Monster[27].name = L"冥队长";
        Monster[27].hp = 3333;
        Monster[27].atk = 1200;
        Monster[27].def = 1133;
        Monster[27].boss = false;
        Monster[27].attrib = 0;
        Monster[27].gold = 112;
        Monster[27].exp = 100;

        Monster[28].name = L"红衣魔王";
        Monster[28].hp = 20000;
        Monster[28].atk = 1333;
        Monster[28].def = 1333;
        Monster[28].boss = false;
        Monster[28].attrib = 0;
        Monster[28].gold = 133;
        Monster[28].exp = 133;
    }
    if(num == 2)//去了21层后提升
    {
        Monster[25].name = L"灵法师";
        Monster[25].hp = 3000;
        Monster[25].atk = 2212;
        Monster[25].def = 1946;
        Monster[25].boss = false;
        Monster[25].attrib = 0;
        Monster[25].gold = 132;
        Monster[25].exp = 116;

        Monster[26].name = L"灵武士";
        Monster[26].hp = 2400;
        Monster[26].atk = 2612;
        Monster[26].def = 2400;
        Monster[26].boss = false;
        Monster[26].attrib = 0;
        Monster[26].gold = 146;
        Monster[26].exp = 125;

        Monster[30].name = L"冥灵魔王";
        Monster[30].hp = 45000;
        Monster[30].atk = 2550;
        Monster[30].def = 2250;
        Monster[30].boss = false;
        Monster[30].attrib = 0;
        Monster[30].gold = 312;
        Monster[30].exp = 275;
    }
    if(num == 3)//22层强化
    {
        Monster[30].name = L"冥灵魔王";
        Monster[30].hp = 60000;
        Monster[30].atk = 3400;
        Monster[30].def = 3000;
        Monster[30].boss = false;
        Monster[30].attrib = 0;
        Monster[30].gold = 390;
        Monster[30].exp = 343;
    }

}

int MainWindow::Calculate(MONSTER Monster)//计算怪物伤害
{
    int times;
    if(Braver.atk <= Monster.def)//勇士攻击力低于怪物防御值，无法攻击返回-1
        return -1;
    else//可以攻击
    {
        times = Monster.hp / (Braver.atk - Monster.def);//攻击次数
        if((Monster.atk - Braver.def) * times > Braver.hp)//勇士血量不够，打不过返回-2
            return -2;
        else {
            if(Monster.atk <= Braver.def)//怪物打不动勇士，返回0
            {
                return 0;
            }
            else {
                return (Monster.atk - Braver.def) * times;//怪物打的动勇士，返回勇士掉血值
            }
        }
    }
}

void MainWindow::isalive()//判断当前楼层怪物是否存活（用于显示怪物信息）
{
    int i,j,k;
    for(k = 12;k <=44;k++)//当前怪物序号为12-19
    {
        for(  i = 0;i < 11;i++)//判断当前层怪物是否存活
        {
            bool find_monster = false;//判断是否找到怪物
            for(  j = 0;j < 11;j++)
            {
                if(floor.Floor[Current_Floor_Num][i][j] == k)
                {
                    find_monster = true;
                    Monster[k-12].alive = true;
                    break;//只要有一个存活直接跳出循环
                }

                else {
                    Monster[k-12].alive = false;
                }
            }
            if(find_monster == true)
            {
                break;
            }
        }
    }
}

void MainWindow::Hide_Before_Game_Scene()//隐藏游戏开始前画面
{  
    this->ui->label_11->hide();
    this->ui->label_14->hide();
    this->ui->label_15->hide();
    this->ui->pushButton->hide();
    this->ui->pushButton_2->hide();
    this->ui->pushButton_3->hide();
    this->ui->textEdit->hide();
}

void MainWindow::Hide_Game_Scene()//隐藏游戏界面
{
    this->ui->graphicsView->hide();
    this->ui->graphicsView_2->hide();
    this->ui->graphicsView_3->hide();
    this->ui->graphicsView_4->hide();
    this->ui->graphicsView_5->hide();
    this->ui->label_13->hide();
    this->ui->label_4->hide();
    this->ui->label_Icon->hide();
    this->ui->label_12->hide();
    this->ui->label_health->hide();
    this->ui->label_health_value->hide();
    this->ui->label_attack->hide();
    this->ui->label_attack_value->hide();
    this->ui->label_defence->hide();
    this->ui->label_defence_value->hide();
    this->ui->label_gold->hide();
    this->ui->label_gold_value->hide();
    this->ui->label_exp->hide();
    this->ui->label_exp_value->hide();
    this->ui->label_YKey->hide();
    this->ui->label_Y_Num->hide();
    this->ui->label_BKey->hide();
    this->ui->label_B_Num->hide();
    this->ui->label_RKey->hide();
    this->ui->label_R_Num->hide();
    this->ui->label_save->hide();
    this->ui->label_quit->hide();
    this->ui->label_access->hide();
    this->ui->label_restart->hide();
    this->ui->widget->hide();
    this->ui->widget_2->hide();
}

void MainWindow::Show_Game_Scene()//展示游戏界面
{
    this->ui->graphicsView->show();
    this->ui->graphicsView_2->show();
    this->ui->graphicsView_3->show();
    this->ui->graphicsView_4->show();
    this->ui->graphicsView_5->show();
    this->ui->label_13->show();
    this->ui->label_4->show();
    this->ui->label_Icon->show();
    this->ui->label_12->show();
    this->ui->label_health->show();
    this->ui->label_health_value->show();
    this->ui->label_attack->show();
    this->ui->label_attack_value->show();
    this->ui->label_defence->show();
    this->ui->label_defence_value->show();
    this->ui->label_gold->show();
    this->ui->label_gold_value->show();
    this->ui->label_exp->show();
    this->ui->label_exp_value->show();
    this->ui->label_YKey->show();
    this->ui->label_Y_Num->show();
    this->ui->label_BKey->show();
    this->ui->label_B_Num->show();
    this->ui->label_RKey->show();
    this->ui->label_R_Num->show();
    this->ui->label_save->show();
    this->ui->label_quit->show();
    this->ui->label_access->show();
    this->ui->label_restart->show();
    this->ui->widget->show();
    this->ui->widget_2->show();
}

void MainWindow::Hide_Fight_Scene()//隐藏战斗窗口
{
    this->ui->label->hide();
    this->ui->label_2->hide();
    this->ui->label_3->hide();
    this->ui->label_5->hide();
    this->ui->label_6->hide();
    this->ui->label_7->hide();
    this->ui->label_8->hide();
    this->ui->label_9->hide();
    this->ui->label_10->hide();
    this->ui->label_25->hide();
    this->ui->label_26->hide();
    this->ui->label_fhp1->hide();
    this->ui->label_fhp2->hide();
    this->ui->label_fatk1->hide();
    this->ui->label_fatk2->hide();
    this->ui->label_fdef1->hide();
    this->ui->label_fdef2->hide();
    this->ui->graphicsView_fight->hide();
    this->ui->graphicsView_monster->hide();
    this->ui->graphicsView_braver->hide();
}

void MainWindow::Show_Fight_Scene()//展示战斗窗口
{
    this->ui->label->show();
    this->ui->label_2->show();
    this->ui->label_3->show();
    this->ui->label_6->show();
    this->ui->label_7->show();
    this->ui->label_8->show();
    this->ui->label_9->show();
    this->ui->label_10->show();
    this->ui->label_25->show();
    this->ui->label_fhp1->show();
    this->ui->label_fhp2->show();
    this->ui->label_fatk1->show();
    this->ui->label_fatk2->show();
    this->ui->label_fdef1->show();
    this->ui->label_fdef2->show();
    this->ui->graphicsView_fight->show();
    this->ui->graphicsView_monster->show();
    this->ui->graphicsView_braver->show();
}

void MainWindow::Handle_Fight()//战斗时窗口内容
{
    Braver.Whether_Press =false;
    Show_Fight_Scene();

    //设置战斗时怪物背景
    QGraphicsScene *scene_fight = new QGraphicsScene;
    scene_fight->setBackgroundBrush(QPixmap::fromImage(ImgFloor));
    QGraphicsPixmapItem* pix_monster = new QGraphicsPixmapItem();
    pix_monster->setPixmap(QPixmap::fromImage(Monster[Monster_temp_num-12].img[display_it]));
    pix_monster->setPos(QPointF(0,0));
    scene_fight->addItem(pix_monster);
    this->ui->graphicsView_monster->setScene(scene_fight);

    //设置战斗时勇士背景
    QGraphicsScene *scene_braver = new QGraphicsScene;
    scene_braver->setBackgroundBrush(QPixmap::fromImage(ImgFloor));
    QGraphicsPixmapItem* pix_braver = new QGraphicsPixmapItem();
    pix_braver->setPixmap(QPixmap::fromImage(ImgBraver[0][0]));
    pix_braver->setPos(QPointF(0,0));
    scene_braver->addItem(pix_braver);
    this->ui->graphicsView_braver->setScene(scene_braver);

    //临时血量存放数据
    int Monster_temp_hp = Monster[Monster_temp_num-12].hp;
    int Monster_temp_damage = Monster[Monster_temp_num-12].atk - Braver.def;
    if(Monster_temp_damage < 0)
        Monster_temp_damage = 0;
    int Braver_temp_damage = Braver.atk - Monster[Monster_temp_num-12].def;

    //如果遇到红衣法师和白衣武士、灵法师，血量不一样
    if(Monster_temp_num == 29)
    {
        Braver_temp_hp -= 300;
        this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    }
    if(Monster_temp_num == 30)
    {
        Braver_temp_hp *= 0.75;
        this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    }
    if(Monster_temp_num == 37)
    {
        Braver_temp_hp *= 0.666;
        this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    }

    //战斗时勇士和怪物状态变化
    this->ui->label_fhp1->setText(QString::number(Monster_temp_hp));
    this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    this->ui->label_fatk1->setText(QString::number(Monster[Monster_temp_num-12].atk));
    this->ui->label_fatk2->setText(QString::number(Braver.atk));
    this->ui->label_fdef1->setText(QString::number(Monster[Monster_temp_num-12].def));
    this->ui->label_fdef2->setText(QString::number(Braver.def));
    this->ui->label_fhp1->setText(QString::number(Monster_temp_hp));
    this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    while (Monster_temp_hp > 0) {
        Sleep(FIGHT_INTERVAL);//战斗攻击间隔
        Monster_temp_hp = Monster_temp_hp - Braver_temp_damage;
        Braver_temp_hp = Braver_temp_hp - Monster_temp_damage;
        if(Monster_temp_hp < 0)
        {
            Monster_temp_hp = 0;
            this->ui->label_fhp1->setText(QString::number(Monster_temp_hp));
            break;
        }
        this->ui->label_fhp1->setText(QString::number(Monster_temp_hp));
        this->ui->label_fhp2->setText(QString::number(Braver_temp_hp));
    }
    this->ui->label_26->show();//显示胜利图片
    Sleep(VICTORY_INTERVAL);
    Hide_Fight_Scene();
    this->ui->label_5->show();//显示获得金币和经验
    QString str = QString("获得金币%1   经验%2").arg(QString::number(Monster[Monster_temp_num-12].gold)).arg(QString::number(Monster[Monster_temp_num-12].exp));
    this->ui->label_5->setText(str);
    Sleep(GOLD_EXP_INTERVAL);
    this->ui->label_5->hide();
    Fight_timer->stop();
    emit Fight_End();
    Braver.Whether_Press = true;
}

void MainWindow::ShowFloor(int k)//展示当前楼层内容
{
    scene_floor->clear();
    int items = 0;
    int i,j;
    for( i = 0;i < 11;i++)
    {
        for( j = 0;j < 11;j++)
        {
            if(floor.Floor[k][i][j] == 0)//地板色
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgFloor));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 1)//明墙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgWall));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 2)//暗墙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgWall));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 3)//黄门
            {
                pixs[items] = new QGraphicsPixmapItem;
                //开门时有定时器，只有当定时器执行完时门位置才会变成勇士，我们在定时器没执行完之前刷新地图,door_x存储门临时位置，不进行下面的判断全图的门会一起打开
                if(door_x == i && door_y == j)
                {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgYDoor[open_door_num]));
                }
                else {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgYDoor[0]));
                }
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 4)//蓝门
            {
                pixs[items] = new QGraphicsPixmapItem;
                if(door_x == i && door_y == j)
                {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgBDoor[open_door_num]));
                }
                else {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgBDoor[0]));
                }
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 5)//红门
            {
                pixs[items] = new QGraphicsPixmapItem;
                if(door_x == i && door_y == j)
                {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgRDoor[open_door_num]));
                }
                else {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgRDoor[0]));
                }
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 6)//小血瓶
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBottle1));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 7)//大血瓶
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBottle2));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 8)//红宝石
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgRGem));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 9)//蓝宝石
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBGem));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 10)//下楼
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgDownstairs));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 11)//上楼
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgUpstairs));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 57)//查看信息
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgInfo));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 58)//黄钥匙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgYKey));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 59)//蓝钥匙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBKey));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 60)//红钥匙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgRKey));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 62)//花门
            {
                pixs[items] = new QGraphicsPixmapItem;
                if(door_x == i && door_y == j)
                {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgGDoor[open_door_num]));
                }
                else {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgGDoor[0]));
                }
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 63)//铁门
            {
                pixs[items] = new QGraphicsPixmapItem;
                if(door_x == i && door_y == j)
                {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgIDoor[open_door_num]));
                }
                else {
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgIDoor[0]));
                }
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 64)//老头
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgNpcOld[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 65)//商人
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgNpcRed[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 66)//岩浆
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgMagma[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 67)//星河
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgGalaxy[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 68)//仙女
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgNpcFairy[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 69)//商店左
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgStoreLeft));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 70)//商店中
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgStoreMiddle[0]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 71)//商店右
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgStoreRight));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 78)//小偷
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgNpcThief[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 79)//大黄钥匙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBigYKey));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 80)//小羽飞燕
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgSLevelUp));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 81)//大金币
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBigGold));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 82)//十字架
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgCross));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 83)//跳楼器
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgChangeFloor));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 84)//榔头
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgHammer));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 85)//大羽飞燕
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgBLevelUp));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 86)//圣水
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgHolyWater));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 87)//公女
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgNpcprincess[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 88)//炎之魔杖
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgMagicWand[0]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 89)//冰之魔杖
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(ImgMagicWand[1]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 43)//血影
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(Monster[31].img[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            else if(floor.Floor[k][i][j] == 44)//魔龙
            {
                pixs[items] = new QGraphicsPixmapItem;
                pixs[items]->setPixmap(QPixmap::fromImage(Monster[32].img[display_it]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }

            if(Braver.pos_x == i && Braver.pos_y == j )//勇士
            {
                pixs[items] = new QGraphicsPixmapItem;
                if (keyUpCnt <= 1)
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgBraver[Braver.face][1]));
                else
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgBraver[Braver.face][0]));
                pixs[items]->setPos(QPointF(48 * j,48 * i));
                scene_floor->addItem(pixs[items]);
                items++;
            }
            for(int m = 0; m < 3 ;m++)//剑
            {
                if(floor.Floor[k][i][j] == m + 72)
                {
                    pixs[items] = new QGraphicsPixmapItem;
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgSword[m]));
                    pixs[items]->setPos(QPointF(48 * j,48 * i));
                    scene_floor->addItem(pixs[items]);
                    items++;
                }
            }
            for(int m = 0; m < 3 ;m++)//盾
            {
                if(floor.Floor[k][i][j] == m + 75)
                {
                    pixs[items] = new QGraphicsPixmapItem;
                    pixs[items]->setPixmap(QPixmap::fromImage(ImgShield[m]));
                    pixs[items]->setPos(QPointF(48 * j,48 * i));
                    scene_floor->addItem(pixs[items]);
                    items++;
                }
            }
            for(int m = 12; m < 12 + MONSTER_NUM;m++)//遇到怪物
            {
                if(floor.Floor[k][i][j] == m)
                {
                    pixs[items] = new QGraphicsPixmapItem;
                    pixs[items]->setPixmap(QPixmap::fromImage(Monster[m-12].img[display_it]));
                    pixs[items]->setPos(QPointF(48 * j,48 * i));
                    scene_floor->addItem(pixs[items]);
                    items++;
                }
            }

        }
    }
    ui->graphicsView_2->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView_2->setFocusPolicy(Qt::NoFocus);//游戏不会因为单击graphicsView_2（存放怪物图片）这个窗口而使得键盘失去焦点
    ui->graphicsView_2->setScene(scene_floor);
    ui->graphicsView_2->setStyleSheet("background:transparent;border:none;");
}

void MainWindow::Handle_Key_Event(int key,int &x,int &y)//处理键盘事件
{
    Braver_temp_hp = Braver.hp;
    if(floor.Floor[Current_Floor_Num][x][y] == 1)// 撞墙则不能动
        return;
    else if(floor.Floor[Current_Floor_Num][x][y] == 3)//撞黄门
    {
        if(Braver.key1 == 0)
            return;
        else {
            Braver.key1 --;
            Open_Door_Animation(x,y);
            Braver.Whether_Press = false;//开门时不可以移动
            Sleep(400);//开门后延时停顿一下
            Braver.Whether_Press = true;
        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 4)//撞蓝门
    {
        if(Braver.key2 == 0)
            return;
        else {
            Open_Door_Animation(x,y);
            Braver.key2 --;
            Braver.Whether_Press = false;
            Sleep(400);//开门后延时停顿一下
            Braver.Whether_Press = true;
        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 5)//撞红门
    {
        if(Braver.key3 == 0)
            return;
        else {
            Open_Door_Animation(x,y);
            Braver.key3 --;
            Braver.Whether_Press = false;
            Sleep(400);//开门后延时停顿一下
            Braver.Whether_Press = true;
        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 6)//小血瓶
    {
        Braver.hp += 150;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得小血瓶
        this->ui->label_5->setText("获得小血瓶,生命值+150");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 7)//大血瓶
    {
        Braver.hp += 500;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得大血瓶
        this->ui->label_5->setText("获得大血瓶,生命值+500");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 8)//红宝石
    {
        Braver.atk += 3;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得红宝石
        this->ui->label_5->setText("获得红宝石,攻击力+3");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 9)//蓝宝石
    {
        Braver.def += 3;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得蓝宝石
        this->ui->label_5->setText("获得蓝宝石，防御力+3");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 10)//下楼
    {
        Current_Floor_Num --;
        //十楼情况特殊，9楼上楼梯位置和十楼下楼梯位置不一样，22楼以后也是
        if(Current_Floor_Num == 10)
        {
            Braver.pos_x = 6;
            Braver.pos_y = 5;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 23 && x ==5 && y ==10)//22层左边楼梯上去的楼（23层）
        {
            Braver.pos_x = 5;
            Braver.pos_y = 0;
            Current_Floor_Num = 23;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 24 && x ==5 && y ==0)//22层右边楼梯上去的楼（24层）
        {
            Braver.pos_x = 5;
            Braver.pos_y = 10;
            Current_Floor_Num = 23;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 25 && x ==0 && y ==5)//22层下边楼梯上去的楼（25层）
        {
            Braver.pos_x = 10;
            Braver.pos_y = 5;
            Current_Floor_Num = 23;
            ShowFloor(Current_Floor_Num);
        }
        //显示楼层
        if(Current_Floor_Num == 24 || Current_Floor_Num == 25 || Current_Floor_Num == 26)
        {
            QString str = QString("第 23 层");
            this->ui->label_4->setText(str);
        }
        if(Current_Floor_Num == 27 || Current_Floor_Num == 28)
        {
            QString str = QString("第 24 层");
            this->ui->label_4->setText(str);
        }
        if(Current_Floor_Num != 28 && Current_Floor_Num != 24 && Current_Floor_Num != 25 && Current_Floor_Num != 26 && Current_Floor_Num != 27)
        {
            //显示第几层
            QString str = QString("第 %1 层").arg(Current_Floor_Num - 1);
            this->ui->label_4->setText(str);
        }

        if(key == 1)//1代表上键
        {
            Braver.pos_x --;
        }
        if(key == 2)//2代表下键
        {
            if(Current_Floor_Num == 1)//处理特殊情况，第一层下楼位置和序章层上楼后位置不一样
            {
                Braver.pos_x = -1;
                Braver.pos_y = 5;
            }
            Braver.pos_x ++;
        }
        if(key == 3)//3代表左键
        {
            Braver.pos_y --;
        }
        if(key == 4)//4代表右键
        {
            Braver.pos_y ++;
        }
        emit UpDownstair_Animation();
        return;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 11)//上楼
    {
        Current_Floor_Num ++;
        Braver.whether_reach_floor[Current_Floor_Num - 1] = true;//代表这一层已经去过，可以飞行
        //去过17层提升怪物属性，且不要每次到17层都重复提升属性
        if(Current_Floor_Num == 18 && Braver.whether_improve_monster_property[0] == false)
        {
            Braver.whether_reach_floor17 = true;
            Braver.whether_improve_monster_property[0] = true;
            Change_Monster_Property(1);
        }
        //去过21层
        if(Current_Floor_Num == 22 && Braver.whether_improve_monster_property[1] == false)
        {
            //Braver.whether_reach_floor17 = true;
            Braver.whether_improve_monster_property[1] = true;
            Change_Monster_Property(2);
        }
        //去过22层
        if(Current_Floor_Num == 23 && Braver.whether_improve_monster_property[2] == false)
        {
            //Braver.whether_reach_floor17 = true;
            Braver.whether_improve_monster_property[2] = true;
            Change_Monster_Property(2);
        }
        //10楼和21,22,23楼上楼后位置特殊
        if(Current_Floor_Num == 11)
        {
            Braver.pos_x = 7;
            Braver.pos_y = 5;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 22)
        {
            Braver.pos_x = 5;
            Braver.pos_y = 5;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 24 && x ==5 && y ==0)//22层左边楼梯
        {
            Braver.pos_x = 5;
            Braver.pos_y = 10;
            Current_Floor_Num = 24;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 24 && x ==5 && y ==10)//22层右边楼梯
        {
            Braver.pos_x = 5;
            Braver.pos_y = 0;
            Current_Floor_Num = 25;
            ShowFloor(Current_Floor_Num);
        }
        if(Current_Floor_Num == 24 && x ==10 && y ==5)//22层下边楼梯
        {
            Braver.pos_x = 0;
            Braver.pos_y = 5;
            Current_Floor_Num = 26;
            ShowFloor(Current_Floor_Num);
        }

        //显示楼层
        if(Current_Floor_Num == 24 || Current_Floor_Num == 25 || Current_Floor_Num == 26)
        {
            QString str = QString("第 23 层");
            this->ui->label_4->setText(str);
        }
        if(Current_Floor_Num == 27 || Current_Floor_Num == 28)
        {
            QString str = QString("第 24 层");
            this->ui->label_4->setText(str);
        }
        if(Current_Floor_Num != 28 && Current_Floor_Num != 24 && Current_Floor_Num != 25 && Current_Floor_Num != 26 && Current_Floor_Num != 27)
        {
            //显示第几层
            QString str = QString("第 %1 层").arg(Current_Floor_Num - 1);
            this->ui->label_4->setText(str);
        }
        if(key == 1)//1代表上键
        {
            if(Current_Floor_Num == 2)//处理特殊情况，序章层上楼后位置和第一层下楼位置不一样
            {
                Braver.pos_x =11;
                Braver.pos_y = 5;
            }
            Braver.pos_x --;
        }
        if(key == 2)//2代表下键
        {
            Braver.pos_x ++;
        }
        if(key == 3)//3代表左键
        {
            Braver.pos_y --;
        }
        if(key == 4)//4代表右键
        {
            Braver.pos_y ++;
        }
        emit UpDownstair_Animation();
        return;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 57)//查看信息
    {
        Braver.Whether_Press = false;
        Braver.Has_Info = true;
        this->ui->label_5->show();//显示获得查看信息装备
        this->ui->label_5->setText("现在你可以按L键来查看怪物信息");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 58)//黄钥匙
    {
        Braver.key1 ++;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得黄钥匙
        this->ui->label_5->setText("获得一把黄钥匙");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 59)//蓝钥匙
    {
        Braver.key2 ++;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得蓝钥匙
        this->ui->label_5->setText("获得一把蓝钥匙");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 60)//红钥匙
    {
        Braver.key3 ++;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得红钥匙
        this->ui->label_5->setText("获得一把红钥匙");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 62)//花门
    {
        //2层花门和小偷对话后才能打开
        if(Current_Floor_Num == 3)
        {
            if(Braver.Speak_Thief == false)
                return;
            else {
                Open_Door_Animation(x,y);
                Braver.Whether_Press = false;//开门时不可以移动
                Sleep(400);//开门后延时停顿一下
                Braver.Whether_Press = true;
            }
        }
        //26层花门打开两种情况，交了魔杖打血影，没交打魔龙
        else if(Current_Floor_Num == 26)
        {
            if(Braver.whether_open_flourdoor == false)//魔龙层
            {
                Open_Door_Animation(x,y);
                Braver.Whether_Press = false;//开门时不可以移动
                Sleep(400);//开门后延时停顿一下
                Current_Floor_Num = 28;
                ShowFloor(Current_Floor_Num);
                Braver.Whether_Press = true;
            }
            else {//血影层
                Open_Door_Animation(x,y);
                Braver.Whether_Press = false;//开门时不可以移动
                Sleep(400);//开门后延时停顿一下
                Current_Floor_Num = 27;
                ShowFloor(Current_Floor_Num);
                Braver.Whether_Press = true;
            }

        }

    }

    else if(floor.Floor[Current_Floor_Num][x][y] == 63)//铁门
    {
        //7层铁门,只有最左边的能打开
        if(Current_Floor_Num == 8)
        {
            if(x == 4 && y == 6)
                return;
            else if(x == 5 && y == 5)
                return;
            else if(x ==3 && y == 5)
                return;
            else {
                Open_Door_Animation(x,y);
                Braver.Whether_Press = false;//开门时不可以移动
                Sleep(400);//开门后延时停顿一下
                Braver.Whether_Press = true;
            }
        }
        //13楼铁门杀了左边冥战士才能开
        else if(Current_Floor_Num == 14)
        {
            if(floor.Floor[14][6][2] != 61)
            {
                return;
            }
            else {
                Open_Door_Animation(x,y);
                Braver.Whether_Press = false;//开门时不可以移动
                Sleep(400);//开门后延时停顿一下
                Braver.Whether_Press = true;
            }
        }
        else if(Current_Floor_Num == 23 || Current_Floor_Num == 24 || Current_Floor_Num == 25  || Current_Floor_Num == 27 || Current_Floor_Num == 28 )
            return;
        else {
            Open_Door_Animation(x,y);
            Braver.Whether_Press = false;//开门时不可以移动
            Sleep(400);//开门后延时停顿一下
            Braver.Whether_Press = true;

        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 64)//老头
    {
        //2楼老头对话
        if(Current_Floor_Num == 3)
        {
            Braver.Dialog_state_num = 2;
            //弹出和老头的对话窗窗口
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //对话完立刻加攻击
            connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
                Braver.Whether_Press = false;
                this->ui->label_5->show();//显示获得钢剑
                this->ui->label_5->setText("得到钢剑，攻击力+30");
                Sleep(GOLD_EXP_INTERVAL);
                this->ui->label_5->hide();
                Braver.Whether_Press = true;
            });
        }
        //5楼老头
        else if(Current_Floor_Num == 6)
        {
            Braver.Dialog_state_num = 6;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        //13楼老头
        else if(Current_Floor_Num == 14)
        {
            Braver.Dialog_state_num = 13;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        //15楼老头对话
        else if(Current_Floor_Num == 16)
        {
            Braver.Dialog_state_num = 14;
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //对话完立刻加攻击
            connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
                Braver.Whether_Press = false;
                if(Braver.exp  < 500)
                {
                    Braver.Whether_Press = true;
                    return;
                }
                else {
                    Braver.exp -=500;
                    Braver.atk += 120;
                    this->ui->label_5->show();//显示获得圣光剑
                    this->ui->label_5->setText("得到圣光剑，攻击力+120");
                    Sleep(GOLD_EXP_INTERVAL);
                    this->ui->label_5->hide();
                }
                this->ui->label_5->hide();
                Braver.Whether_Press = true;
            });
        }
        //16楼老头对话
        else if(Current_Floor_Num == 17)
        {
            Braver.Dialog_state_num = 17;
            Braver.Speak_old16 = true;
            Braver.Whether_Press = false;
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            Braver.Whether_Press = true;
        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 65)//商人
    {
        //2楼商人
        if(Current_Floor_Num == 3)
        {
            Braver.Dialog_state_num = 3;
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //对话完立刻加防御
            connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
                Braver.Whether_Press = false;
                this->ui->label_5->show();//显示获得钢盾
                this->ui->label_5->setText("得到钢盾，防御力+30");
                Sleep(GOLD_EXP_INTERVAL);
                this->ui->label_5->hide();
                Braver.Whether_Press = true;
            });
        }
        //5楼商人
        else if(Current_Floor_Num == 6)
        {
            Braver.Dialog_state_num = 7;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        //12楼商人
        else if(Current_Floor_Num == 13)
        {
            Braver.Dialog_state_num = 12;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        //15楼商人
        else if(Current_Floor_Num == 16)
        {
            Braver.Dialog_state_num = 15;
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //对话完立刻加防御
            connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
                Braver.Whether_Press = false;
                if(Braver.gold  < 500)
                {
                    Braver.Whether_Press = true;
                    return;
                }
                else {
                    Braver.gold -=500;
                    Braver.def += 120;
                    this->ui->label_5->show();//显示获得圣光盾
                    this->ui->label_5->setText("得到圣光盾，防御力+120");
                    Sleep(GOLD_EXP_INTERVAL);
                    this->ui->label_5->hide();
                }
                Braver.Whether_Press = true;
            });
        }
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 66)//岩浆
        return;
    else if(floor.Floor[Current_Floor_Num][x][y] == 67)//星河
        return;
    else if(floor.Floor[Current_Floor_Num][x][y] == 68)//仙女
    {
        if(Current_Floor_Num == 1)//1楼仙女
        {
            //首次和仙女对话
            if(Braver.Speak_Fairy == false && Braver.Has_Cross == false && Braver.Speak_old16 == false)
            {
                Braver.Dialog_state_num = 0;//首次和仙女对话
                Braver.Speak_Fairy = true;
                //弹出和仙女的对话窗窗口
                dialogwindow = new DialogWindow(this);
                dialogwindow->move(300,300);
                dialogwindow->setFocus();
                dialogwindow->show();
                this->setFocusPolicy(Qt::NoFocus);
                //仙女给完钥匙立刻刷新地图
                connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                    ShowData();
                });
                //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                connect(dialogwindow,&DialogWindow::Exit,this,[=](){//对完话仙女左移一格
                    floor.Floor[1][8][5] = 0;
                    floor.Floor[1][8][4] = 68;
                    this->setFocusPolicy(Qt::StrongFocus);
                });
            }
            //和16楼老头对完话后和仙女对话打开24层
            else if(Braver.Speak_Fairy == true && Braver.Speak_old16 == true && Braver.Speak_fairy_afterold == false  )
            {
                Braver.Dialog_state_num = 16;//和16楼老头对完话后和仙女对话打开24层对话框
                Braver.Speak_fairy_afterold = true;
                //弹出和仙女的对话窗窗口
                dialogwindow = new DialogWindow(this);
                dialogwindow->move(300,300);
                dialogwindow->setFocus();
                dialogwindow->show();
                this->setFocusPolicy(Qt::NoFocus);
                //仙女提升完能力立刻显示
                connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                    ShowData();
                });
                //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                    this->setFocusPolicy(Qt::StrongFocus);
                });
            }

            //拿到十字架后和仙女对话提升能力对话框
            else if((Braver.Has_Cross == true && Braver.Summit_Cross == false && Braver.Speak_old16 == false) || (Braver.Speak_fairy_afterold == true && Braver.Summit_Cross == false) )
            {
                Braver.Dialog_state_num = 1;//拿到十字架后和仙女对话提升能力对话框
                //弹出和仙女的对话窗窗口
                dialogwindow = new DialogWindow(this);
                dialogwindow->move(300,300);
                dialogwindow->setFocus();
                dialogwindow->show();
                this->setFocusPolicy(Qt::NoFocus);
                //仙女提升完能力立刻显示
                connect(dialogwindow,&DialogWindow::Update_State,this,[=](){
                    ShowData();
                });
                //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                    floor.Floor[21][7][5] = 11;//对完话能上21楼
                    this->setFocusPolicy(Qt::StrongFocus);
                });
            }

            //完成上述操作后，不会再触发对话框
            else if((Braver.Speak_Fairy == true && Braver.Has_Cross == false) || (Braver.Speak_Fairy == true && Braver.Summit_Cross == true)){
                this->setFocus();
                this->setFocusPolicy(Qt::StrongFocus);
            }
        }
        else if(Current_Floor_Num == 23)//22楼仙女
        {
            //首次和仙女对话
            if(Braver.Speak_Fairy22 == false && (Braver.whether_get_magic_wand[0] == false ||Braver.whether_get_magic_wand[1] == false ))
            {
                Braver.Dialog_state_num = 24;//首次和仙女对话
                Braver.Speak_Fairy22 = true;
                //弹出和仙女的对话窗窗口
                dialogwindow = new DialogWindow(this);
                dialogwindow->move(300,300);
                dialogwindow->setFocus();
                dialogwindow->show();
                this->setFocusPolicy(Qt::NoFocus);
                //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                    this->setFocusPolicy(Qt::StrongFocus);
                });
            }
            //集齐灵杖后仙女对话
            if( Braver.whether_get_magic_wand[0] == true && Braver.whether_get_magic_wand[1] == true && Braver.whether_summit_magic_wand == false)
            {
                Braver.Dialog_state_num = 25;//集齐魔杖后仙女对话
                Braver.whether_summit_magic_wand = true;
                Braver.whether_open_flourdoor = true;
                //弹出和仙女的对话窗窗口
                dialogwindow = new DialogWindow(this);
                dialogwindow->move(300,300);
                dialogwindow->setFocus();
                dialogwindow->show();
                this->setFocusPolicy(Qt::NoFocus);
                //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                    this->setFocusPolicy(Qt::StrongFocus);
                });
            }
            else if(Braver.whether_summit_magic_wand == true && Braver.Speak_Fairy22 == true)
            {return;}
        }
        return;
    }

    else if(floor.Floor[Current_Floor_Num][x][y] == 69 || floor.Floor[Current_Floor_Num][x][y] == 70 || floor.Floor[Current_Floor_Num][x][y] == 71)//商店
    {
        if(Current_Floor_Num == 4)//3楼商店
        {
            Braver.Dialog_state_num = 8;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        else if(Current_Floor_Num == 12)//11楼商店
        {
            Braver.Dialog_state_num = 10;
            storewindow = new StoreWindow(this);
            storewindow->move(300,0);
            storewindow->setFocus();
            storewindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在商店界面操作时，主窗口勇士状态信息实时更新，没有这个函数，商店购买后必须关闭商店界面在走一步属性才变化。
            connect(storewindow,&StoreWindow::Update_State,this,[=](){
                ShowData();
            });
            //当在商店界面操作时，主窗口不可动，关闭商店后才可操作主窗口。
            connect(storewindow,&StoreWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
    }

    else if(floor.Floor[Current_Floor_Num][x][y] == 72)//铁剑
    {
        Braver.atk += 10;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得铁剑
        this->ui->label_5->setText("获得铁剑，攻击力+10");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 73)//青光剑
    {
        Braver.atk += 70;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得青光剑
        this->ui->label_5->setText("获得青光剑，攻击力+70");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 74)//神圣剑
    {
        Braver.atk += 150;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得神圣剑
        this->ui->label_5->setText("获得神圣剑，攻击力+150");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 75)//铁盾
    {
        Braver.def += 10;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得铁盾
        this->ui->label_5->setText("获得铁盾，防御力+10");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 76)//青光盾
    {
        Braver.def += 70;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得青光盾
        this->ui->label_5->setText("获得青光盾，防御力+70");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 77)//神圣盾
    {
        Braver.def += 150;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得神圣盾
        this->ui->label_5->setText("获得神圣盾，防御力+150");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 78)//小偷
    {
        //首次和小偷对话
        if(Braver.Speak_Thief == false && Braver.Has_Hammer == false)
        {
            Braver.Dialog_state_num = 4;
            //弹出和小偷的对话窗窗口
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                this->setFocusPolicy(Qt::StrongFocus);
            });
            return;
        }
        //拿到榔头和小偷对话，打通18层
        else if(Braver.Speak_Thief == true && Braver.Has_Hammer == true)
        {
            Braver.Dialog_state_num = 5;
            //弹出和小偷的对话窗窗口
            dialogwindow = new DialogWindow(this);
            dialogwindow->move(300,300);
            dialogwindow->setFocus();
            dialogwindow->show();
            this->setFocusPolicy(Qt::NoFocus);
            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                floor.Floor[19][9][5] = 0;
                floor.Floor[19][8][5] = 0;
                this->setFocusPolicy(Qt::StrongFocus);
            });
        }
        else if(Braver.Speak_Thief == true && Braver.Has_Hammer == false){
            this->setFocus();
            this->setFocusPolicy(Qt::StrongFocus);
            return;
        }

    }

    else if(floor.Floor[Current_Floor_Num][x][y] == 79)//大黄钥匙
    {
        Braver.key1 ++;
        Braver.key2 ++;
        Braver.key3 ++;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得大黄钥匙
        this->ui->label_5->setText("获得大黄钥匙，所有钥匙数+1");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 80)//小羽飞燕
    {
        Braver.level += 1;
        Braver.hp += 1000;
        Braver.atk += 10;
        Braver.def += 10;
        ShowData();
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得小羽飞燕
        this->ui->label_5->setText("获得小羽飞燕，等级+1");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }

    else if(floor.Floor[Current_Floor_Num][x][y] == 81)//大金币
    {
        Braver.gold += 300;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示大金币
        this->ui->label_5->setText("获得超大金币，金币+300");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 82)//十字架
    {
        Braver.Has_Cross = true;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示十字架
        this->ui->label_5->setText("获得十字架，将它交给仙子会得到大幅提升");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 83)//跳楼器
    {
        Braver.Has_Change_Floor = true;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示跳楼器
        this->ui->label_5->setText("获得楼层飞行器，按J键可以在楼层之间飞行");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 84)//榔头
    {
        Braver.Has_Hammer = true;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示榔头
        this->ui->label_5->setText("获得十字镐，将他交给小偷吧，看看会发生什么");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 85)//大羽飞燕
    {
        Braver.level += 3;
        Braver.hp += 3000;
        Braver.atk += 30;
        Braver.def += 30;
        ShowData();
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得大羽飞燕
        this->ui->label_5->setText("获得大羽飞燕，等级+3");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 86)//圣水
    {
        Braver.hp *= 2;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示获得圣水
        this->ui->label_5->setText("获得圣水，生命值翻倍");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 87)//公主
    {
        Braver.Dialog_state_num = 20;//和公主对话
        //弹出和公主的对话窗窗口
        dialogwindow = new DialogWindow(this);
        dialogwindow->move(300,300);
        dialogwindow->setFocus();
        dialogwindow->show();
        this->setFocusPolicy(Qt::NoFocus);
        //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
        connect(dialogwindow,&DialogWindow::Exit,this,[=](){//和公主对话后出现19层入口
            floor.Floor[19][10][10] = 11;
            ShowFloor(Current_Floor_Num);
            this->setFocusPolicy(Qt::StrongFocus);
        });
        return;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 88)//炎之魔杖
    {
        Braver.whether_get_magic_wand[0] = true;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示炎之魔杖
        this->ui->label_5->setText("获得炎之魔杖");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(floor.Floor[Current_Floor_Num][x][y] == 89)//冰之魔杖
    {
        Braver.whether_get_magic_wand[1] = true;
        Braver.Whether_Press = false;
        this->ui->label_5->show();//显示冰之魔杖
        this->ui->label_5->setText("获得冰之魔杖");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    else if(Current_Floor_Num == 17 && x ==4 && y ==5 && Braver.Speak_Devils16 == false)//与16楼魔王对话
    {
        Braver.Dialog_state_num = 18;//和16楼魔王对话
        //弹出和魔王的对话窗窗口
        dialogwindow = new DialogWindow(this);
        dialogwindow->move(300,300);
        dialogwindow->setFocus();
        dialogwindow->show();
        this->setFocusPolicy(Qt::NoFocus);
        //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
        connect(dialogwindow,&DialogWindow::Exit,this,[=](){
            Braver.Speak_Devils16 = true;
            this->setFocusPolicy(Qt::StrongFocus);
        });
        return;
    }

    else if(Current_Floor_Num == 20 && x ==7 && y ==5 && Braver.Speak_Devils19 == false)//与19楼魔王对话
    {
        Braver.Dialog_state_num = 19;//和19楼魔王对话
        //弹出和魔王的对话窗窗口
        dialogwindow = new DialogWindow(this);
        dialogwindow->move(300,300);
        dialogwindow->setFocus();
        dialogwindow->show();
        this->setFocusPolicy(Qt::NoFocus);
        //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
        connect(dialogwindow,&DialogWindow::Exit,this,[=](){
            Braver.Speak_Devils19 = true;
            this->setFocusPolicy(Qt::StrongFocus);
        });
        return;
    }

    for(int i = 0;i < MONSTER_NUM; i++)//遇到怪物的处理
    {
        if(floor.Floor[Current_Floor_Num][x][y] == i + 12)//怪物序号顺序排列
        {
            if(Calculate(Monster[i]) < 0)
            {
                qDebug()<<"打不过";
                return;
            }
            //遇到麻衣法师，直接扣100血
            else if(floor.Floor[Current_Floor_Num][x][y] == 31)
            {
                if( Braver.hp - 100 - Calculate(Monster[19]) <= 0)
                {
                    return;
                }
                else {
                    Braver.hp -= 100;
                    Braver.hp -= Calculate(Monster[19]);
                    Braver.gold += Monster[19].gold;
                    Braver.exp += Monster[19].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 31;
                }

            }

            //遇到红衣法师，直接扣300血
            else if(floor.Floor[Current_Floor_Num][x][y] == 29)
            {
                if( Braver.hp - 300 - Calculate(Monster[17]) <= 0)
                {
                    return;
                }
                else {
                    Braver.hp -= 300;
                    Braver.hp -= Calculate(Monster[17]);
                    Braver.gold += Monster[17].gold;
                    Braver.exp += Monster[17].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 29;
                }

            }
            //遇到白衣武士，先扣1/4的血
            else if(floor.Floor[Current_Floor_Num][x][y] == 30)
            {

                if(Braver.hp * 0.75 - Calculate(Monster[18]) <= 0)
                {
                    return;
                }
                else {
                    Braver.hp *= 0.75;
                    Braver.hp -= Calculate(Monster[18]);
                    Braver.gold += Monster[18].gold;
                    Braver.exp += Monster[18].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 30;
                }
            }
            //碰到灵法师，先扣1/3的血
            else if(floor.Floor[Current_Floor_Num][x][y] == 37)
            {

                if(Braver.hp * 0.666666 - Calculate(Monster[25]) <= 0)
                {
                    return;
                }
                else {
                    Braver.hp *= 0.666666;
                    Braver.hp -= Calculate(Monster[25]);
                    Braver.gold += Monster[25].gold;
                    Braver.exp += Monster[25].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 37;
                }
            }
            //碰到红衣魔王,只和17层的死后交流
            else if(floor.Floor[Current_Floor_Num][x][y] == 40)
            {
                if(Current_Floor_Num == 17)
                {
                    Braver.hp -= Calculate(Monster[28]);
                    Braver.gold += Monster[28].gold;
                    Braver.exp += Monster[28].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 40;
                    Braver.Dialog_state_num = 21;
                    connect(this,&MainWindow::Fight_End,this,[=](){
                        if(Braver.Dialog_state_num == 21)
                        {
                            qDebug()<<"h";
                            //弹出和魔王的对话窗窗口
                            dialogwindow = new DialogWindow(this);
                            dialogwindow->move(300,300);
                            dialogwindow->setFocus();
                            dialogwindow->show();
                            this->setFocusPolicy(Qt::NoFocus);
                            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                                this->setFocusPolicy(Qt::StrongFocus);
                            });
                        }
                    });
                }
                else {
                    Braver.hp -= Calculate(Monster[28]);
                    Braver.gold += Monster[28].gold;
                    Braver.exp += Monster[28].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 40;
                }
            }
            //碰到冥灵魔王
            else if(floor.Floor[Current_Floor_Num][x][y] == 42)
            {
                if(Current_Floor_Num == 20)//19层冥灵魔王
                {
                    Braver.hp -= Calculate(Monster[30]);
                    Braver.gold += Monster[30].gold;
                    Braver.exp += Monster[30].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = 42;
                    Braver.Dialog_state_num = 22;//和19楼魔王死后对话
                    connect(this,&MainWindow::Fight_End,this,[=](){
                        if(Braver.Dialog_state_num == 22)
                        {
                            qDebug()<<"l";
                            //弹出和魔王的对话窗窗口
                            dialogwindow = new DialogWindow(this);
                            dialogwindow->move(300,300);
                            dialogwindow->setFocus();
                            dialogwindow->show();
                            this->setFocusPolicy(Qt::NoFocus);
                            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                                this->setFocusPolicy(Qt::StrongFocus);
                            });
                        }

                    });

                }
                else if(Current_Floor_Num == 22 && Braver.Speak_fairy_afterold == false)//游戏结局1
                {
                    Braver.hp -= Calculate(Monster[i]);
                    Braver.gold += Monster[i].gold;
                    Braver.exp += Monster[i].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = i + 12;
                    Braver.Dialog_state_num = 23;//和19楼魔王死后对话
                    connect(this,&MainWindow::Fight_End,this,[=](){
                        if(Braver.Dialog_state_num == 23)
                        {
                            qDebug()<<"l";
                            //弹出和魔王的对话窗窗口
                            dialogwindow = new DialogWindow(this);
                            dialogwindow->move(300,300);
                            dialogwindow->setFocus();
                            dialogwindow->show();
                            this->setFocusPolicy(Qt::NoFocus);
                            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                                this->setFocusPolicy(Qt::StrongFocus);
                            });
                        }

                    });
                    floor.Floor[22][6][5] = 0;
                }
                else if(Current_Floor_Num == 22 && Braver.Speak_fairy_afterold == true)//继续打24层
                {
                    Braver.hp -= Calculate(Monster[i]);
                    Braver.gold += Monster[i].gold;
                    Braver.exp += Monster[i].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = i + 12;
                    Braver.Dialog_state_num = 23;//和19楼魔王死后对话
                    connect(this,&MainWindow::Fight_End,this,[=](){
                        if(Braver.Dialog_state_num == 23)
                        {
                            qDebug()<<"l";
                            //弹出和魔王的对话窗窗口
                            dialogwindow = new DialogWindow(this);
                            dialogwindow->move(300,300);
                            dialogwindow->setFocus();
                            dialogwindow->show();
                            this->setFocusPolicy(Qt::NoFocus);
                            //当在对话框操作时，主窗口不可动，关闭对话框后才可操作主窗口。
                            connect(dialogwindow,&DialogWindow::Exit,this,[=](){
                                this->setFocusPolicy(Qt::StrongFocus);
                            });
                        }

                    });
                    //打开通往22层楼梯，同时可退回20层
                    floor.Floor[22][6][5] = 0;
                    floor.Floor[22][0][5] = 11;                   
                }
                else {
                    Braver.hp -= Calculate(Monster[i]);
                    Braver.gold += Monster[i].gold;
                    Braver.exp += Monster[i].exp;
                    Fight_timer->start(0);
                    Monster_temp_num = i + 12;
                    }
            }
            else {
                Braver.Dialog_state_num = 26;//遇到怪物Dialog_state_num改变，不然会出现对话框
                Braver.hp -= Calculate(Monster[i]);
                Braver.gold += Monster[i].gold;
                Braver.exp += Monster[i].exp;
                Fight_timer->start(0);
                Monster_temp_num = i + 12;
            }
        }
    }

    if(floor.Floor[Current_Floor_Num][x][y] != 3)
    {
        if(key == 1)//1代表上键
        {
            Braver.pos_x --;
        }
        if(key == 2)//2代表下键
        {
            Braver.pos_x ++;
        }
        if(key == 3)//3代表左键
        {
            Braver.pos_y --;
        }
        if(key == 4)//4代表右键
        {
            Braver.pos_y ++;
        }
        floor.Floor[Current_Floor_Num][x][y] = 61;//下一步走到的地方原来图片消失，变成勇士。
    }
    ShowData();
    ShowFloor(Current_Floor_Num );
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int target_posx,target_posy;//勇士下一步到的目标位置
    if(event->key() == Qt::Key_Up && Braver.Whether_Press ==true) //向上
    {
        keyUpCnt = 0;
        Braver.face = 3;
        if(Braver.pos_x == 0)//地图边缘检测
            return;
        target_posx = Braver.pos_x - 1;
        target_posy = Braver.pos_y;//未来位置
        Handle_Key_Event(1,target_posx,target_posy);
        qDebug()<<"x="<<Braver.pos_x<<"y="<<Braver.pos_y;
    }

    if(event->key() == Qt::Key_Down && Braver.Whether_Press ==true) //向下
    {
        keyUpCnt = 0;
        Braver.face = 0;
        if(Braver.pos_x == 10)//地图边缘检测
            return;
        target_posx = Braver.pos_x + 1;
        target_posy = Braver.pos_y;//未来位置
        Handle_Key_Event(2,target_posx,target_posy);
        qDebug()<<"x="<<Braver.pos_x<<"y="<<Braver.pos_y;
    }

    if(event->key() == Qt::Key_Left && Braver.Whether_Press ==true) //向左
    {
        keyUpCnt = 0;
        Braver.face = 1;
        if(Braver.pos_y == 0)//地图边缘检测
            return;
        target_posx = Braver.pos_x;
        target_posy = Braver.pos_y - 1;//未来位置
        Handle_Key_Event(3,target_posx,target_posy);
        qDebug()<<"x="<<Braver.pos_x<<"y="<<Braver.pos_y;
    }

    if(event->key() == Qt::Key_Right && Braver.Whether_Press ==true) //向右
    {
        keyUpCnt = 0;
        Braver.face = 2;
        if(Braver.pos_y == 10)//地图边缘检测
            return;
        target_posx = Braver.pos_x;
        target_posy = Braver.pos_y + 1;//未来位置
        Handle_Key_Event(4,target_posx,target_posy);
        qDebug()<<"x="<<Braver.pos_x<<"y="<<Braver.pos_y;
    }

    if(event->key() == Qt::Key_R )//重启游戏
    {
        ReGame();
        Braver.Whether_Press = false;
        this->ui->label_5->show();//提示重启成功
        this->ui->label_5->setText("重启游戏成功");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    if(event->key() == Qt::Key_S )//保存游戏
    {
        Save_Game();
        Braver.Whether_Press = false;
        this->ui->label_5->show();//提示保存成功
        this->ui->label_5->setText("保存游戏成功");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    if(event->key() == Qt::Key_A )//读取游戏
    {
        Load_Game();
        ShowFloor(Braver.save_floor_num);
        Braver.Whether_Press = false;
        this->ui->label_5->show();//提示读取成功
        this->ui->label_5->setText("读取游戏成功");
        Sleep(GOLD_EXP_INTERVAL);
        this->ui->label_5->hide();
        Braver.Whether_Press = true;
    }
    if(event->key() == Qt::Key_L/* && Braver.Has_Info == true */){ //查看怪物手册
        Braver.Whether_Press =false;
        if(L_Num == 0)
        {
            MonsterInfoList* monstor_list = new MonsterInfoList(ui->listWidget);
            monstor_list->setFixedSize(528,528);
            isalive();//判断怪物是否存活，存活才在列表上显示
            for(int m = MONSTER_NUM;m >= 0;m --)
            {
                if(Monster[m].alive)
                {
                    vtemp.push_back(m);//将存活的怪物序号放入数组中
                }
            }
            monstor_list->addItem();
            ui->listWidget->show();
            L_Num ++;
        }
        else if(L_Num == 1)//再次按L键关闭界面
        {
            vtemp.clear();//关闭信息列表后必须清空数组，否则出问题
            extern_timer->stop();//定时器必须关闭，否则也会出问题
            ui->listWidget->close();
            Braver.Whether_Press =true;
            this->setFocus();//焦点回到主窗口
            L_Num = 0;
        }
    }

    if(event->key() == Qt::Key_J/* && Braver.Has_Change_Floor == true */){ //跳楼
        Braver.Dialog_state_num = 11;
        //去过的楼层才能飞,测试先关闭此功能
        for(int i =0;i < FLOOR_NUM;i++)
        {
            Braver.whether_reach_floor[i] = true;
        }
        changefloorwindow = new ChangeFloor(this);
        changefloorwindow->move(200,100);
        changefloorwindow->setFocus();
        changefloorwindow->show();
        this->setFocusPolicy(Qt::NoFocus);

        //选择要跳跃的楼层并更换楼层
        connect(changefloorwindow,&ChangeFloor::Select_Floor,this,[=](){
            Current_Floor_Num = Braver.temp_floor + 1;


            //换楼后位置在上楼梯口处
            if(Current_Floor_Num == 1)
            {
                Braver.pos_x = floor.stairs_pos[0][0];
                Braver.pos_y = floor.stairs_pos[0][1];
            }
            else if(Current_Floor_Num == 2)
            {
                Braver.pos_x = floor.stairs_pos[1][0];
                Braver.pos_y = floor.stairs_pos[1][1];
            }
            else if(Current_Floor_Num == 3)
            {
                Braver.pos_x = floor.stairs_pos[2][0];
                Braver.pos_y = floor.stairs_pos[2][1];
            }
            else if(Current_Floor_Num == 4)
            {
                Braver.pos_x = floor.stairs_pos[3][0];
                Braver.pos_y = floor.stairs_pos[3][1];
            }
            else if(Current_Floor_Num == 5)
            {
                Braver.pos_x = floor.stairs_pos[4][0];
                Braver.pos_y = floor.stairs_pos[4][1];
            }
            else if(Current_Floor_Num == 6)
            {
                Braver.pos_x = floor.stairs_pos[5][0];
                Braver.pos_y = floor.stairs_pos[5][1];
            }
            else if(Current_Floor_Num == 7)
            {
                Braver.pos_x = floor.stairs_pos[6][0];
                Braver.pos_y = floor.stairs_pos[6][1];
            }
            else if(Current_Floor_Num == 8)
            {
                Braver.pos_x = floor.stairs_pos[7][0];
                Braver.pos_y = floor.stairs_pos[7][1];
            }
            else if(Current_Floor_Num == 9)
            {
                Braver.pos_x = floor.stairs_pos[8][0];
                Braver.pos_y = floor.stairs_pos[8][1];
            }
            else if(Current_Floor_Num == 10)
            {
                Braver.pos_x = floor.stairs_pos[9][0];
                Braver.pos_y = floor.stairs_pos[9][1];
            }
            else if(Current_Floor_Num == 11)
            {
                Braver.pos_x = floor.stairs_pos[10][0];
                Braver.pos_y = floor.stairs_pos[10][1];
            }
            else if(Current_Floor_Num == 12)
            {
                Braver.pos_x = floor.stairs_pos[11][0];
                Braver.pos_y = floor.stairs_pos[11][1];
            }
            else if(Current_Floor_Num == 13)
            {
                Braver.pos_x = floor.stairs_pos[12][0];
                Braver.pos_y = floor.stairs_pos[12][1];
            }
            else if(Current_Floor_Num == 14)
            {
                Braver.pos_x = floor.stairs_pos[13][0];
                Braver.pos_y = floor.stairs_pos[13][1];
            }
            else if(Current_Floor_Num == 15)
            {
                Braver.pos_x = floor.stairs_pos[14][0];
                Braver.pos_y = floor.stairs_pos[14][1];
            }
            else if(Current_Floor_Num == 16)
            {
                Braver.pos_x = floor.stairs_pos[15][0];
                Braver.pos_y = floor.stairs_pos[15][1];
            }
            else if(Current_Floor_Num == 17)
            {
                Braver.pos_x = floor.stairs_pos[16][0];
                Braver.pos_y = floor.stairs_pos[16][1];
            }
            else if(Current_Floor_Num == 18)
            {
                Braver.pos_x = floor.stairs_pos[17][0];
                Braver.pos_y = floor.stairs_pos[17][1];
            }
            else if(Current_Floor_Num == 19)
            {
                Braver.pos_x = floor.stairs_pos[18][0];
                Braver.pos_y = floor.stairs_pos[18][1];
            }
            else if(Current_Floor_Num == 20)
            {
                Braver.pos_x = floor.stairs_pos[19][0];
                Braver.pos_y = floor.stairs_pos[19][1];
            }
            else if(Current_Floor_Num == 21)
            {
                Braver.pos_x = floor.stairs_pos[20][0];
                Braver.pos_y = floor.stairs_pos[20][1];
            }
            Braver.face = 0;
            //显示第几层
            QString str = QString("第 %1 层").arg(Current_Floor_Num - 1);
            this->ui->label_4->setText(str);
            this->setFocusPolicy(Qt::StrongFocus);
            ShowFloor(Braver.temp_floor);
            changefloorwindow->close();
            emit UpDownstair_Animation();

        });

        //按esc键退出选楼窗口
        connect(changefloorwindow,&ChangeFloor::Exit,this,[=](){
            this->setFocusPolicy(Qt::StrongFocus);
            changefloorwindow->close();
        });
    }

    if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 9)//关闭游戏开始时的文字窗口。
    {
        this->ui->graphicsView_7->hide();
        this->ui->textEdit->hide();
        this->ui->textBrowser->hide();
        Show_Game_Scene();
        Text_timer->stop();
        this->setFocus();//焦点回到主窗口
    }

    if(event->key() == Qt::Key_Escape)//关闭其他窗口，回到游戏窗口。
    {
        //关闭怪物信息列表
        vtemp.clear();
        extern_timer->stop();
        ui->listWidget->close();
        Braver.Whether_Press =true;
        this->setFocus();//焦点回到主窗口
    }
    if(event->key() == Qt::Key_I)//飞到22层快捷键
    {
        Current_Floor_Num = 23;
        ShowFloor(Current_Floor_Num);
        this->setFocus();//焦点回到主窗口
    }
}

void MainWindow::Sleep(int msec)//延时函数
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::Gradual_Change_Animation()//上下楼转场渐变动画
{
    m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(ui->graphicsView_7);
    m_pGraphicsOpacityEffect->setOpacity(1);
    ui->graphicsView_7->setGraphicsEffect(m_pGraphicsOpacityEffect);

    m_pNameAnimation = new QPropertyAnimation(m_pGraphicsOpacityEffect,"opacity",this);
    m_pNameAnimation->setEasingCurve(QEasingCurve::Linear);
    m_pNameAnimation->setDuration(GRADUAL_CHANGE_INTERVAL);

    //上楼时，收到Upstair_Animation信号，做一个转场动画
    connect(this,&MainWindow::UpDownstair_Animation,this,[=](){
        this->ui->graphicsView_7->show();
        ShowFloor(Current_Floor_Num );
        Braver.Whether_Press = false;//动画时按键失灵
        m_pNameAnimation->setStartValue(1);
        m_pNameAnimation->setEndValue(0);
        m_pNameAnimation->start(QAbstractAnimation::KeepWhenStopped);
        Sleep(900);//延迟一小会恢复
        Braver.Whether_Press = true;
    });
}

void MainWindow::Open_Door_Animation(int p_x,int p_y)//开门动画
{
    //临时存储钥匙位置
    door_x = p_x;
    door_y = p_y;
    Open_Door_timer = new QTimer(this);
    Open_Door_timer->start();
    Open_Door_timer->setInterval(100);
    //定时器开启后，目标位置还是门，刷新地图显示开门动画过程，显示最后一张图后，目标位置变成勇士。
    connect(Open_Door_timer,&QTimer::timeout,this,[=](){
        open_door_num ++;
        ShowFloor(Current_Floor_Num);
        if(open_door_num == 3)
        {
            open_door_num = 0;
            floor.Floor[Current_Floor_Num][p_x][p_y] = 61;
            Open_Door_timer->stop();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

