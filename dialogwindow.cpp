#include "dialogwindow.h"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
    Count_Num = 0;
    Init();
}

void DialogWindow::Init()
{
    Hide_Window();
    if(Braver.Dialog_state_num == 0)//首次和仙子对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  ……");
    }
    else if(Braver.Dialog_state_num == 1)//拿到十字架后和仙子对话
        {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  仙子，我已经将那个十字架找到了。");
    }
    else if(Braver.Dialog_state_num == 2)//2楼老头
        {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  您已经得救了！");
    }
    else if(Braver.Dialog_state_num == 3)//2楼商人
        {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  您已经得救了！");
    }
    else if(Braver.Dialog_state_num == 4)//首次和小偷对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  你已经得救了！");
    }
    else if(Braver.Dialog_state_num == 5)//拿到榔头和小偷对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  哈，快看！我找到了什么");
    }
    else if(Braver.Dialog_state_num == 14)//15楼老头
    {
        this->ui->graphicsView_old->show();
        this->ui->textBrowser->setText("神秘老人:\r  你好，勇敢的孩子，你终于来到这了。");
    }
    else if(Braver.Dialog_state_num == 15)//15楼商人
    {
        this->ui->graphicsView_red->show();
        this->ui->textBrowser->setText("商人:\r  啊哈，欢迎你的到来。我这里有一件对你来说");
    }
    else if(Braver.Dialog_state_num == 16)//和16楼老头对完话和仙子对话
    {
        this->ui->graphicsView_fairy->show();
        this->ui->textBrowser->setText("仙子:\r  嗯？！你手里的那个东西是什么？");
    }
    else if(Braver.Dialog_state_num == 17)//和16楼老头对话
    {
        this->ui->graphicsView_old->show();
        this->ui->textBrowser->setText("神秘老人:\r  年轻人，你终于来了");
    }
    else if(Braver.Dialog_state_num == 18)//和16楼魔王对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  ……");
    }
    else if(Braver.Dialog_state_num == 19)//和17楼魔王对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  大魔头，你的死期到了！");
    }
    else if(Braver.Dialog_state_num == 20)//和公主对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  公主，你得救了！");
    }
    else if(Braver.Dialog_state_num == 21)//和16楼魔王死后对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  快把公主交出来！");
    }
    else if(Braver.Dialog_state_num == 22)//和19楼魔王死后对话
    {
        this->ui->graphicsView_devil19->show();
        this->ui->textBrowser->setText("冥灵魔王:\r  看不出来你还有两下子，有本领的话来21楼。");
    }
    else if(Braver.Dialog_state_num == 23)//和21楼魔王死后对话
    {
        this->ui->graphicsView_devil19->show();
        this->ui->textBrowser->setText("冥灵魔王:\r  啊……\r  怎么可能，我怎么可能");
    }
    if(Braver.Dialog_state_num == 24)//首次和22楼仙子对话
    {
        this->ui->graphicsView_fairy->show();
        this->ui->textBrowser->setText("仙子:\r  做的很好，现在你已经将那个可恶的冥灵魔王");
    }
    if(Braver.Dialog_state_num == 25)//集齐灵杖后22楼仙子对话
    {
        this->ui->graphicsView_braver->show();
        this->ui->textBrowser->setText("勇士:\r  快看，我找到所有的灵杖了");
    }

    //space闪烁效果
    int k =0;
    int count =0;

    space_timer = new QTimer(this);
    space_timer->start();
    space_timer->setInterval(400);
    connect(space_timer,&QTimer::timeout,this,[=]()mutable{
        count++;
        if(count % 2 ==0)
            k =255;
        else {
            k = 75;
        }
        ui->textBrowser_2->setTextColor(QColor(255,255,255,k));
        ui->textBrowser_2->setText("--space--");
    });

    this->ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ImgFairy = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgBraver= QImage(":/Graphics/Characters/002-Braver01.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgThief = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 64, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgNpcOld = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 0, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgNpcRed = QImage(":/Graphics/Characters/001-npc01.png").copy(0, 32, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );
    ImgDevil16 = QImage(":/Graphics/Characters/010-Monster08.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    ImgDevil19 = QImage(":/Graphics/Characters/004-Monster02.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    ImgPrincess = QImage(":/Graphics/Characters/001-npc02.png").copy(0, 96, 32, 32).scaled(48,48,Qt::KeepAspectRatioByExpanding );

    //仙女头像
    QGraphicsScene *scene_fairy = new QGraphicsScene;
    scene_fairy->addPixmap(QPixmap::fromImage(ImgFairy));
    this->ui->graphicsView_fairy->setScene(scene_fairy);
    this->ui->graphicsView_fairy->setStyleSheet("background:transparent;border:none;");

    //勇士头像
    QGraphicsScene *scene_braver = new QGraphicsScene;
    scene_braver->addPixmap(QPixmap::fromImage(ImgBraver));
    this->ui->graphicsView_braver->setScene(scene_braver);
    this->ui->graphicsView_braver->setStyleSheet("background:transparent;border:none;");

    //小偷头像
    QGraphicsScene *scene_thief = new QGraphicsScene;
    scene_thief->addPixmap(QPixmap::fromImage(ImgThief));
    this->ui->graphicsView_thief->setScene(scene_thief);
    this->ui->graphicsView_thief->setStyleSheet("background:transparent;border:none;");

    //老头头像
    QGraphicsScene *scene_old = new QGraphicsScene;
    scene_old->addPixmap(QPixmap::fromImage(ImgNpcOld));
    this->ui->graphicsView_old->setScene(scene_old);
    this->ui->graphicsView_old->setStyleSheet("background:transparent;border:none;");

    //商人头像
    QGraphicsScene *scene_red = new QGraphicsScene;
    scene_red->addPixmap(QPixmap::fromImage(ImgNpcRed));
    this->ui->graphicsView_red->setScene(scene_red);
    this->ui->graphicsView_red->setStyleSheet("background:transparent;border:none;");

    //16楼魔王头像
    QGraphicsScene *scene_devil16 = new QGraphicsScene;
    scene_devil16->addPixmap(QPixmap::fromImage(ImgDevil16));
    this->ui->graphicsView_devil16->setScene(scene_devil16);
    this->ui->graphicsView_devil16->setStyleSheet("background:transparent;border:none;");

    //19楼魔王头像
    QGraphicsScene *scene_devil19 = new QGraphicsScene;
    scene_devil19->addPixmap(QPixmap::fromImage(ImgDevil19));
    this->ui->graphicsView_devil19->setScene(scene_devil19);
    this->ui->graphicsView_devil19->setStyleSheet("background:transparent;border:none;");

    // 公主头像
    QGraphicsScene *scene_princess = new QGraphicsScene;
    scene_princess->addPixmap(QPixmap::fromImage(ImgPrincess));
    this->ui->graphicsView_princess->setScene(scene_princess);
    this->ui->graphicsView_princess->setStyleSheet("background:transparent;border:none;");
}

void DialogWindow::Hide_Window()
{
    this->ui->graphicsView_fairy->hide();
    this->ui->graphicsView_thief->hide();
    this->ui->graphicsView_old->hide();
    this->ui->graphicsView_red->hide();
    this->ui->graphicsView_braver->hide();
    this->ui->graphicsView_devil16->hide();
    this->ui->graphicsView_devil19->hide();
    this->ui->graphicsView_princess->hide();
}

void DialogWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 0) //空格键且状态0（首次和仙女对话）
    {
        Count_Num ++ ;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  你醒了!");
        }

        else if(Count_Num == 2)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  ……\r  你是谁？我在那里？");
        }

        else if(Count_Num == 3)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  我是这里的仙子，刚才你被这里的小怪打昏了。");
        }
        else if(Count_Num == 4)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  ……\r  剑，剑，我的剑呢？");
        }
        else if(Count_Num == 5)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  你的剑被他们抢走了，我只来得及将你救出来。");
        }
        else if(Count_Num == 6)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  那公主呢？我是来救公主的。");
        }
        else if(Count_Num == 7)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  公主还在里面，你这样进去是打不过里面的小怪的。");
        }
        else if(Count_Num == 8)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  那怎么办，我答应了国王一定要把公主救出来的，那我现在应该怎");
        }
        else if(Count_Num == 9)
        {
            this->ui->textBrowser->setText("勇士:\r么办呢？");
        }
        else if(Count_Num == 10)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  放心吧，我把我的力量借给你，你就可以打赢这些小怪了。");
        }
        else if(Count_Num == 11)
            {
            this->ui->textBrowser->setText("仙女:\r  不过，你得先帮我去找一样东西，找到了再来这里找我。");
        }
        else if(Count_Num == 12)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  找东西？找什么东西？");
        }
        else if(Count_Num == 13)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  是一个十字架，中间有一颗红色的宝石。");
        }
        else if(Count_Num == 14)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  那东西有什么用吗？");
        }
        else if(Count_Num == 15)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  我本来是这座塔的守护者，可不久前，从北方来了一批恶魔，他们");
        }
        else if(Count_Num == 16)
            {
            this->ui->textBrowser->setText("仙女:\r占领了这座塔，并将我的魔力封在了这个十字架中，如果你能将它带");
        }
        else if(Count_Num == 17)
            {
            this->ui->textBrowser->setText("仙女:\r出塔来，那我的魔力就会慢慢恢复，到那时我便可以把力量借给你去");
        }
        else if(Count_Num == 18)
            {
            this->ui->textBrowser->setText("仙女:\r救公主了。要记住：只有用我的魔力才可以打开二十一层的门。");
        }
        else if(Count_Num == 19)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  ……\r  好吧，我试试看。");
        }
        else if(Count_Num == 20)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  刚才我去看过了，你的剑被放在三楼，你的盾在五楼上，而那个十");
        }
        else if(Count_Num == 21)
            {
            this->ui->textBrowser->setText("仙女:\r字架被放在七楼。要到七楼，你得先取回你的剑和盾。");
        }
        else if(Count_Num == 22)
            {
            this->ui->textBrowser->setText("仙女:\r  另外，在塔的其他楼层上，还有一些存放了好几百年的宝剑和宝物");
        }
        else if(Count_Num == 23)
            {
            this->ui->textBrowser->setText("仙女:\r如果得到它们，对于你对付这里的怪物将有很大的帮助。");
        }
        else if(Count_Num == 24)
        {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  ……\r  可是，我怎么进去呢？");
        }
        else if(Count_Num == 25)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  我这里有三把钥匙，你先拿去，在塔里还有很多这样的钥匙。");
        }
        else if(Count_Num == 26)
            {
            this->ui->textBrowser->setText("仙女:\r  你一定要珍惜使用。勇敢去去吧，勇士！");
            //这里地图要刷新显示钥匙增加了
            Braver.key1 += 1;
            Braver.key2 += 1;
            Braver.key3 += 1;
            emit Update_State();
        }
        else if(Count_Num == 27)
        {
            Count_Num = 0;
            Hide_Window();
            space_timer->stop();
            Braver.Speak_Fairy = true;
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 1) //空格键且状态1（拿到十字架后和仙女对话）
        {
        Count_Num++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  你做的很好。\r  那么，现在我就开始授予");
        }
        else if(Count_Num == 2)
            {
            this->ui->textBrowser->setText("仙女:\r  你更强的力量。\r  唵嘛呢叭咪吽！");
        }
        else if(Count_Num == 3)
            {
            this->ui->textBrowser->setText("仙女:\r  好了，我已经将你现在的能力提升了！");
        }
        else if(Count_Num == 4)
            {
            this->ui->textBrowser->setText("仙女:\r  记住，如果你没有足够的能力的话，不要去第二十一层！");
        }
        else if(Count_Num == 5)
            {
            this->ui->textBrowser->setText("仙女:\r  在那一层里，你所有宝物的法力都会失去作用！");
        }
        else if(Count_Num == 6)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            Braver.hp *= 1.3;
            Braver.atk *= 1.3;
            Braver.def *= 1.3;
            Braver.Summit_Cross = true;
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 16) //空格键且状态16（和16楼老头对过话后和仙女对话）
        {
        Count_Num++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  这个？这个是一个老人交给我的，是他让我带它来");
        }
        else if(Count_Num == 2)
            {
            this->ui->textBrowser->setText("勇士:\r  找你的。他说你知道它的来历和作用。");
        }
        else if(Count_Num == 3)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  这是以前的圣者留下来的。他们一共有三个，你这个叫");
        }
        else if(Count_Num == 4)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  心之魔杖，应该还有一个镶有蓝宝石的“冰之灵杖和镶有红宝石的");
        }
        else if(Count_Num == 5)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  炎之灵杖，如果不把他们找齐的话天下会大乱的。");
        }
        else if(Count_Num == 6)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  好，那我就去把他们全部找到！");
        }
        else if(Count_Num == 7)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 2) //空格键且状态2（和2楼老头对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_old->show();
            this->ui->textBrowser->setText("神秘老头:\r  哦，我的孩子，真是太感谢你了");
        }
        else if(Count_Num == 2 )
            {
            this->ui->textBrowser->setText("神秘老头:\r  这个地方又脏又坏，我真是快呆不下去了。");
        }
        else if(Count_Num == 3 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_old->hide();
            this->ui->textBrowser->setText("勇士:\r  快走吧，我还得救被关在这里的公主。");
        }
        else if(Count_Num == 4 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_old->show();
            this->ui->textBrowser->setText("神秘老头:\r  哦，你是来救公主的，为了表示对你的感谢，");
        }
        else if(Count_Num == 5 )
            {
            this->ui->textBrowser->setText("神秘老头:\r  这个东西就送给你吧，这还是我年轻时候用过的。");
        }
        else if(Count_Num == 6 )
            {
            this->ui->textBrowser->setText("神秘老头:\r  拿着它去解救公主吧！");
        }
        else if(Count_Num == 7)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            Braver.atk += 30;
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 3) //空格键且状态3（和2楼商人对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_red->show();
            this->ui->textBrowser->setText("商人:\r  哦，是嘛！真是太感谢你了！");
        }
        else if(Count_Num == 2  )
            {
            this->ui->textBrowser->setText("商人:\r  我是个商人，不知道为什么被抓到这里来了。");
        }
        else if(Count_Num == 3  )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_red->hide();
            this->ui->textBrowser->setText("勇士:\r  快走吧，现在您已经自由了。");
        }
        else if(Count_Num == 4  )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_red->show();
            this->ui->textBrowser->setText("商人:\r  哦，对对对，我已经自由了。");
        }
        else if(Count_Num == 5  )
            {
            this->ui->textBrowser->setText("商人:\r  那这个东西就给你吧，本来是准备卖钱的。");
        }
        else if(Count_Num == 6  )
            {
            this->ui->textBrowser->setText("商人:\r  相信他对你一定很有帮助！");
        }
        else if(Count_Num == 7)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            Braver.def += 30;
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 4) //空格键且状态4（首次和小偷对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  啊，那真是太好了，我又可以在这里面寻宝了！");
        }
        else if(Count_Num == 2)
            {
            this->ui->textBrowser->setText("小偷:\r  哦，我还没有自我介绍，我叫杰克，是这附近有名的小偷，什么金银财");
        }
        else if(Count_Num == 3)
            {
            this->ui->textBrowser->setText("小偷:\r  宝我样样都偷过。不过这次运气可不太好，刚进来就被抓了。");
        }
        else if(Count_Num == 4)
            {
            this->ui->textBrowser->setText("小偷:\r  现在你帮我打开了门，那我就帮你做一件事吧。");
        }
        else if(Count_Num == 5)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_thief->hide();
            this->ui->textBrowser->setText("勇士:\r  快走吧，外面还有很多怪物，我可能顾不上你。");
        }
        else if(Count_Num == 6)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  不，不，不会有事的。快说吧，叫我做什么？");
        }
        else if(Count_Num == 7)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_thief->hide();
            this->ui->textBrowser->setText("勇士:\r  ……\r  你会开门吗？");
        }
        else if(Count_Num == 8)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  那当然。");
        }
        else if(Count_Num == 9)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_thief->hide();
            this->ui->textBrowser->setText("勇士:\r  那就请你帮我打开第二层的门吧！");
        }
        else if(Count_Num == 10)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  那个简单，不过，如果你能帮我找到一把嵌了红");
        }
        else if(Count_Num == 11)
            {
            this->ui->textBrowser->setText("小偷:\r  宝石的铁榔头的话，我还帮你打通第十八层的路。");
        }
        else if(Count_Num == 12)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_thief->hide();
            this->ui->textBrowser->setText("勇士:\r  嵌了红宝石的铁榔头？\r  好吧，那我帮你找找。");
        }
        else if(Count_Num == 13)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  非常感谢，一会我便会将第二层的门打开。");
        }
        else if(Count_Num == 14)
            {
            this->ui->textBrowser->setText("小偷:\r  如果你找到那个铁榔头的话，还是来这里找我！");
        }
        else if(Count_Num == 15)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            Braver.Speak_Thief = true;
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 5) //空格键且状态5（拿到榔头和小偷对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_thief->show();
            this->ui->textBrowser->setText("小偷:\r  太好了，这个东西果然在这里！");
        }
        else if(Count_Num == 2)
            {
            this->ui->textBrowser->setText("小偷:\r  好吧，我这就去帮你修好第18层的路面。");
        }

        else if(Count_Num == 3)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }
    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 15) //空格键且状态15（和15楼商人对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_red->show();
            this->ui->textBrowser->setText("商人:\r 非常好的宝物，只要你出得起500块，我就卖给你。");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_red->hide();
            this->ui->textBrowser->setText("勇士:\r  好的，成交");
        }
        else if(Count_Num == 3)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 14) //空格键且状态14（和15楼老头对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_old->show();
            this->ui->textBrowser->setText("神秘老头:\r  我将给你一个非常好的宝物，他可以使你的攻击");
        }
        else if(Count_Num == 2 )
            {
            this->ui->textBrowser->setText("神秘老头:\r  力提升120点，但这必须用你的500点经验来换取。");
        }
        else if(Count_Num == 3 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_old->hide();
            this->ui->textBrowser->setText("勇士:\r  好吧，那就将那把剑给我吧。");
        }

        else if(Count_Num == 4)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 17) //空格键且状态17（和16楼老头对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_old->hide();
            this->ui->textBrowser->setText("勇士:\r ……");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_old->show();
            this->ui->textBrowser->setText("神秘老头:\r  我已经快封不住他了，请你将这个东西交给彩蝶。");
        }
        else if(Count_Num == 3 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_old->hide();
            this->ui->textBrowser->setText("勇士:\r  您怎么了？");
        }
        else if(Count_Num == 4 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_old->show();
            this->ui->textBrowser->setText("神秘老头:\r  快去吧，再迟就来不及了");
        }
        else if(Count_Num == 5)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 18) //空格键且状态18（和16楼魔王对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil16->show();
            this->ui->textBrowser->setText("红衣魔王:\r  停止吧！愚蠢的人类！");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_devil16->hide();
            this->ui->textBrowser->setText("勇士:\r  该停止的是你！魔王。快说，公主关在哪里？");
        }
        else if(Count_Num == 3 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil16->show();
            this->ui->textBrowser->setText("红衣魔王:\r  呵！你先打败我再说吧。");
        }

        else if(Count_Num == 4)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 19) //空格键且状态19（和17楼魔王对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil19->show();
            this->ui->textBrowser->setText("冥灵魔王:\r  哈哈哈省略号\r  你也真是有意思，别以");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil19->show();
            this->ui->textBrowser->setText("冥灵魔王:\r  为蝶仙给你点力量就能打败我，你还早着呢！");
        }
        else if(Count_Num == 3)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 20) //空格键且状态20（和公主对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_princess->show();
            this->ui->textBrowser->setText("公主:\r  啊，你是来救我得嘛？");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_princess->hide();
            this->ui->textBrowser->setText("勇士:\r  是的，我现在就带你离开。");
        }
        else if(Count_Num == 3 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_princess->show();
            this->ui->textBrowser->setText("公主:\r  不，我还不想走。");
        }
        else if(Count_Num == 4 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_princess->hide();
            this->ui->textBrowser->setText("勇士:\r  请你快随我出去吧！");
        }
        else if(Count_Num == 5 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_princess->show();
            this->ui->textBrowser->setText("公主:\r  我不要就这样走，我要看着那个恶魔被杀死！");
        }
        else if(Count_Num == 6 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_princess->show();
            this->ui->textBrowser->setText("公主:\r  等你杀了那个恶魔我就和你一起出去！");
        }
        else if(Count_Num == 7 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_princess->hide();
            this->ui->textBrowser->setText("勇士:\r  大恶魔？我已经杀死了一个魔王。");
        }
        else if(Count_Num == 8 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_princess->show();
            this->ui->textBrowser->setText("公主:\r  你杀死的是一个小头目，真正的魔王非常厉害，请你一定要杀死他。");
        }
        else if(Count_Num == 9 )
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_princess->hide();
            this->ui->textBrowser->setText("勇士:\r  好，那你等我好消息！");
        }

        else if(Count_Num == 10)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 21) //空格键且状态21（和16楼魔王死后对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil16->show();
            this->ui->textBrowser->setText("红衣魔王:\r  你等着，我的老大会给我报仇的");
        }
        else if(Count_Num == 2 )
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil16->show();
            this->ui->textBrowser->setText("红衣魔王:\r  公主正在被嘿嘿嘿呢，哈哈哈哈！");
        }
        else if(Count_Num == 3)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 22) //空格键且状态22（和19楼魔王死后对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil19->show();
            this->ui->textBrowser->setText("冥灵魔王:\r  在那里，你就可以见识到我的真正实力了！");
        }
        else if(Count_Num == 2)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 23) //空格键且状态23（和21楼魔王死后对话）
        {
        Count_Num ++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_devil19->show();
            this->ui->textBrowser->setText("冥灵魔王:\r  会被你打败呢！\r  不，不要这样……");
        }
        else if(Count_Num == 2)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 24) //空格键且状态24（和22楼仙女对话）
        {
        Count_Num++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙子:\r  给杀了，快去找另外的两根“灵杖”吧，找齐了以后");
        }
        else if(Count_Num == 2)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  把他们一起交给我，我帮你解开最后的封印！");
        }
        else if(Count_Num == 3)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  记住，如果不把封印解开的话，最底层的怪物你永远打不过！");
        }
        else if(Count_Num == 4)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Update_State();
            emit Exit();
            this->close();
        }
    }

    else if(event->key() == Qt::Key_Space && Braver.Dialog_state_num == 25) //空格键且状态25（找到灵杖后和22楼仙女对话）
        {
        Count_Num++;
        if(Count_Num == 1)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙子:\r  嗯，不错，现在我们可以解除这里面的封印了");
        }
        else if(Count_Num == 2)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  那我们开始吧！玛尼玛尼哄！");
        }
        else if(Count_Num == 3)
            {
            this->ui->graphicsView_braver->show();
            this->ui->graphicsView_fairy->hide();
            this->ui->textBrowser->setText("勇士:\r  ……");
        }
        else if(Count_Num == 4)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  ……\r  好了，我已经将他们三个力量注入了，但你要记住：");
        }
        else if(Count_Num == 5)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  没有足够的实力之前，千万不要进入那个花形门。");
        }
        else if(Count_Num == 6)
            {
            this->ui->graphicsView_braver->hide();
            this->ui->graphicsView_fairy->show();
            this->ui->textBrowser->setText("仙女:\r  一旦你进入那个花形门，你就再也回不来了！");
        }
        else if(Count_Num == 7)
        {
            Count_Num = 0;
            space_timer->stop();
            Hide_Window();
            emit Update_State();
            emit Exit();
            this->close();
        }
    }
}
DialogWindow::~DialogWindow()
{
    delete ui;
}
