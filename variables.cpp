#include "variables.h"

BRAVER Braver;
MONSTER Monster[MONSTER_NUM];
floor_data floor;
vector<int> vtemp;
QTimer* extern_timer;

void init_monsters() //初始化全局变量
{    
    Monster[0].name = L"绿色史莱姆";
    Monster[0].hp = 50;
    Monster[0].atk = 20;
    Monster[0].def = 1;
    Monster[0].boss = false;
    Monster[0].attrib = 0;
    Monster[0].gold = 1;
    Monster[0].exp = 1;
    Monster[0].img[0] = QImage(":/Graphics/Characters/003-Monster01.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[0].img[1] = QImage(":/Graphics/Characters/003-Monster01.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[0].alive = true;

    Monster[1].name = L"红色史莱姆";
    Monster[1].hp = 70;
    Monster[1].atk = 15;
    Monster[1].def = 2;
    Monster[1].boss = false;
    Monster[1].attrib = 0;
    Monster[1].gold = 2;
    Monster[1].exp = 2;
    Monster[1].img[0] = QImage(":/Graphics/Characters/003-Monster01.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[1].img[1] = QImage(":/Graphics/Characters/003-Monster01.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[1].alive = true;

    Monster[2].name = L"黑色史莱姆";
    Monster[2].hp = 200;
    Monster[2].atk = 35;
    Monster[2].def = 10;
    Monster[2].boss = false;
    Monster[2].attrib = 0;
    Monster[2].gold = 5;
    Monster[2].exp = 5;
    Monster[2].img[0] = QImage(":/Graphics/Characters/003-Monster01.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[2].img[1] = QImage(":/Graphics/Characters/003-Monster01.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[2].alive = true;

    Monster[3].name = L"骷髅人";
    Monster[3].hp = 110;
    Monster[3].atk = 25;
    Monster[3].def = 5;
    Monster[3].boss = false;
    Monster[3].attrib = 0;
    Monster[3].gold = 5;
    Monster[3].exp = 4;
    Monster[3].img[0] = QImage(":/Graphics/Characters/005-Monster03.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[3].img[1] = QImage(":/Graphics/Characters/005-Monster03.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[3].alive = true;

    Monster[4].name = L"骷髅士兵";
    Monster[4].hp = 150;
    Monster[4].atk = 40;
    Monster[4].def = 20;
    Monster[4].boss = false;
    Monster[4].attrib = 0;
    Monster[4].gold = 8;
    Monster[4].exp = 6;
    Monster[4].img[0] = QImage(":/Graphics/Characters/005-Monster03.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[4].img[1] = QImage(":/Graphics/Characters/005-Monster03.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[4].alive = true;


    Monster[5].name = L"初级法师";
    Monster[5].hp = 125;
    Monster[5].atk = 50;
    Monster[5].def = 25;
    Monster[5].boss = false;
    Monster[5].attrib = 0;
    Monster[5].gold = 10;
    Monster[5].exp = 7;
    Monster[5].img[0] = QImage(":/Graphics/Characters/007-Monster05.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[5].img[1] = QImage(":/Graphics/Characters/007-Monster05.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[5].alive = true;

    Monster[6].name = L"小蝙蝠";
    Monster[6].hp = 100;
    Monster[6].atk = 20;
    Monster[6].def = 5;
    Monster[6].boss = false;
    Monster[6].attrib = 0;
    Monster[6].gold = 3;
    Monster[6].exp = 3;
    Monster[6].img[0] = QImage(":/Graphics/Characters/004-Monster02.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[6].img[1] = QImage(":/Graphics/Characters/004-Monster02.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[6].alive = true;

    Monster[7].name = L"兽面人";
    Monster[7].hp = 300;
    Monster[7].atk = 75;
    Monster[7].def = 45;
    Monster[7].boss = false;
    Monster[7].attrib = 0;
    Monster[7].gold = 13;
    Monster[7].exp = 10;
    Monster[7].img[0] = QImage(":/Graphics/Characters/006-Monster04.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[7].img[1] = QImage(":/Graphics/Characters/006-Monster04.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[7].alive = true;

    Monster[8].name = L"金卫士";
    Monster[8].hp = 850;
    Monster[8].atk = 350;
    Monster[8].def = 200;
    Monster[8].boss = false;
    Monster[8].attrib = 0;
    Monster[8].gold = 45;
    Monster[8].exp = 40;
    Monster[8].img[0] = QImage(":/Graphics/Characters/009-Monster07.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[8].img[1] = QImage(":/Graphics/Characters/009-Monster07.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[8].alive = true;

    Monster[9].name = L"金队长";
    Monster[9].hp = 900;
    Monster[9].atk = 750;
    Monster[9].def = 650;
    Monster[9].boss = false;
    Monster[9].attrib = 0;
    Monster[9].gold = 77;
    Monster[9].exp = 70;
    Monster[9].img[0] = QImage(":/Graphics/Characters/009-Monster07.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[9].img[1] = QImage(":/Graphics/Characters/009-Monster07.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[9].alive = true;

    Monster[10].name = L"初级卫兵";
    Monster[10].hp = 450;
    Monster[10].atk = 150;
    Monster[10].def = 90;
    Monster[10].boss = false;
    Monster[10].attrib = 0;
    Monster[10].gold = 22;
    Monster[10].exp = 19;
    Monster[10].img[0] = QImage(":/Graphics/Characters/008-Monster06.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[10].img[1] = QImage(":/Graphics/Characters/008-Monster06.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[10].alive = true;

    Monster[11].name = L"大蝙蝠";
    Monster[11].hp = 150;
    Monster[11].atk = 60;
    Monster[11].def = 30;
    Monster[11].boss = false;
    Monster[11].attrib = 0;
    Monster[11].gold = 10;
    Monster[11].exp = 8;
    Monster[11].img[0] = QImage(":/Graphics/Characters/004-Monster02.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[11].img[1] = QImage(":/Graphics/Characters/004-Monster02.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[11].alive = true;

    Monster[12].name = L"红蝙蝠";
    Monster[12].hp = 550;
    Monster[12].atk = 160;
    Monster[12].def = 90;
    Monster[12].boss = false;
    Monster[12].attrib = 0;
    Monster[12].gold = 25;
    Monster[12].exp = 20;
    Monster[12].img[0] = QImage(":/Graphics/Characters/004-Monster02.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[12].img[1] = QImage(":/Graphics/Characters/004-Monster02.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[12].alive = true;

    Monster[13].name = L"高级法师";
    Monster[13].hp = 100;
    Monster[13].atk = 200;
    Monster[13].def = 110;
    Monster[13].boss = false;
    Monster[13].attrib = 0;
    Monster[13].gold = 30;
    Monster[13].exp = 25;
    Monster[13].img[0] = QImage(":/Graphics/Characters/007-Monster05.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[13].img[1] = QImage(":/Graphics/Characters/007-Monster05.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[13].alive = true;

    Monster[14].name = L"骷髅队长";
    Monster[14].hp = 400;
    Monster[14].atk = 90;
    Monster[14].def = 50;
    Monster[14].boss = false;
    Monster[14].attrib = 0;
    Monster[14].gold = 15;
    Monster[14].exp = 12;
    Monster[14].img[0] = QImage(":/Graphics/Characters/005-Monster03.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[14].img[1] = QImage(":/Graphics/Characters/005-Monster03.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[14].alive = true;

    Monster[15].name = L"石头怪人";
    Monster[15].hp = 500;
    Monster[15].atk = 115;
    Monster[15].def = 65;
    Monster[15].boss = false;
    Monster[15].attrib = 0;
    Monster[15].gold = 15;
    Monster[15].exp = 15;
    Monster[15].img[0] = QImage(":/Graphics/Characters/006-Monster04.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[15].img[1] = QImage(":/Graphics/Characters/006-Monster04.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[15].alive = true;

    Monster[16].name = L"怪王";
    Monster[16].hp = 700;
    Monster[16].atk = 250;
    Monster[16].def = 125;
    Monster[16].boss = false;
    Monster[16].attrib = 0;
    Monster[16].gold = 32;
    Monster[16].exp = 30;
    Monster[16].img[0] = QImage(":/Graphics/Characters/003-Monster01.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[16].img[1] = QImage(":/Graphics/Characters/003-Monster01.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[16].alive = true;

    Monster[17].name = L"红衣法师";
    Monster[17].hp = 500;
    Monster[17].atk = 400;
    Monster[17].def = 260;
    Monster[17].boss = false;
    Monster[17].attrib = 0;
    Monster[17].gold = 47;
    Monster[17].exp = 45;
    Monster[17].img[0] = QImage(":/Graphics/Characters/007-Monster05.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[17].img[1] = QImage(":/Graphics/Characters/007-Monster05.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[17].alive = true;

    Monster[18].name = L"白衣武士";
    Monster[18].hp = 1300;
    Monster[18].atk = 300;
    Monster[18].def = 150;
    Monster[18].boss = false;
    Monster[18].attrib = 0;
    Monster[18].gold = 45;
    Monster[18].exp = 35;
    Monster[18].img[0] = QImage(":/Graphics/Characters/010-Monster08.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[18].img[1] = QImage(":/Graphics/Characters/010-Monster08.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[18].alive = true;

    Monster[19].name = L"麻衣法师";
    Monster[19].hp = 250;
    Monster[19].atk = 120;
    Monster[19].def = 70;
    Monster[19].boss = false;
    Monster[19].attrib = 0;
    Monster[19].gold = 20;
    Monster[19].exp = 17;
    Monster[19].img[0] = QImage(":/Graphics/Characters/007-Monster05.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[19].img[1] = QImage(":/Graphics/Characters/007-Monster05.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[19].alive = true;

    Monster[20].name = L"兽面武士";
    Monster[20].hp = 900;
    Monster[20].atk = 450;
    Monster[20].def = 330;
    Monster[20].boss = false;
    Monster[20].attrib = 0;
    Monster[20].gold = 50;
    Monster[20].exp = 50;
    Monster[20].img[0] = QImage(":/Graphics/Characters/006-Monster04.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[20].img[1] = QImage(":/Graphics/Characters/006-Monster04.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[20].alive = true;

    Monster[21].name = L"冥卫兵";
    Monster[21].hp = 1250;
    Monster[21].atk = 500;
    Monster[21].def = 400;
    Monster[21].boss = false;
    Monster[21].attrib = 0;
    Monster[21].gold = 55;
    Monster[21].exp = 55;
    Monster[21].img[0] = QImage(":/Graphics/Characters/008-Monster06.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[21].img[1] = QImage(":/Graphics/Characters/008-Monster06.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[21].alive = true;

    Monster[22].name = L"高级卫兵";
    Monster[22].hp = 1500;
    Monster[22].atk = 560;
    Monster[22].def = 460;
    Monster[22].boss = false;
    Monster[22].attrib = 0;
    Monster[22].gold = 60;
    Monster[22].exp = 60;
    Monster[22].img[0] = QImage(":/Graphics/Characters/008-Monster06.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[22].img[1] = QImage(":/Graphics/Characters/008-Monster06.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[22].alive = true;

    Monster[23].name = L"双手剑士";
    Monster[23].hp = 1200;
    Monster[23].atk = 620;
    Monster[23].def = 520;
    Monster[23].boss = false;
    Monster[23].attrib = 0;
    Monster[23].gold = 65;
    Monster[23].exp = 75;
    Monster[23].img[0] = QImage(":/Graphics/Characters/008-Monster06.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[23].img[1] = QImage(":/Graphics/Characters/008-Monster06.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[23].alive = true;

    Monster[24].name = L"冥战士";
    Monster[24].hp = 2000;
    Monster[24].atk = 680;
    Monster[24].def = 590;
    Monster[24].boss = false;
    Monster[24].attrib = 0;
    Monster[24].gold = 70;
    Monster[24].exp = 65;
    Monster[24].img[0] = QImage(":/Graphics/Characters/009-Monster07.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[24].img[1] = QImage(":/Graphics/Characters/009-Monster07.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[24].alive = true;

    Monster[25].name = L"灵法师";
    Monster[25].hp = 1500;
    Monster[25].atk = 830;
    Monster[25].def = 730;
    Monster[25].boss = false;
    Monster[25].attrib = 0;
    Monster[25].gold = 80;
    Monster[25].exp = 70;
    Monster[25].img[0] = QImage(":/Graphics/Characters/010-Monster08.png").copy(0,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[25].img[1] = QImage(":/Graphics/Characters/010-Monster08.png").copy(64,64,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[25].alive = true;

    Monster[26].name = L"灵武士";
    Monster[26].hp = 1200;
    Monster[26].atk = 980;
    Monster[26].def = 900;
    Monster[26].boss = false;
    Monster[26].attrib = 0;
    Monster[26].gold = 88;
    Monster[26].exp = 75;
    Monster[26].img[0] = QImage(":/Graphics/Characters/009-Monster07.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[26].img[1] = QImage(":/Graphics/Characters/009-Monster07.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[26].alive = true;

    Monster[27].name = L"冥队长";
    Monster[27].hp = 2500;
    Monster[27].atk = 900;
    Monster[27].def = 850;
    Monster[27].boss = false;
    Monster[27].attrib = 0;
    Monster[27].gold = 84;
    Monster[27].exp = 75;
    Monster[27].img[0] = QImage(":/Graphics/Characters/005-Monster03.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[27].img[1] = QImage(":/Graphics/Characters/005-Monster03.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[27].alive = true;

    Monster[28].name = L"红衣魔王";
    Monster[28].hp = 15000;
    Monster[28].atk = 1000;
    Monster[28].def = 1000;
    Monster[28].boss = false;
    Monster[28].attrib = 0;
    Monster[28].gold = 100;
    Monster[28].exp = 100;
    Monster[28].img[0] = QImage(":/Graphics/Characters/010-Monster08.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[28].img[1] = QImage(":/Graphics/Characters/010-Monster08.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[28].alive = true;

    Monster[29].name = L"影子战士";
    Monster[29].hp = 3100;
    Monster[29].atk = 1150;
    Monster[29].def = 1050;
    Monster[29].boss = false;
    Monster[29].attrib = 0;
    Monster[29].gold = 92;
    Monster[29].exp = 80;
    Monster[29].img[0] = QImage(":/Graphics/Characters/006-Monster04.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[29].img[1] = QImage(":/Graphics/Characters/006-Monster04.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[29].alive = true;

    Monster[30].name = L"冥灵魔王";
    Monster[30].hp = 30000;
    Monster[30].atk = 1700;
    Monster[30].def = 1500;
    Monster[30].boss = false;
    Monster[30].attrib = 0;
    Monster[30].gold = 250;
    Monster[30].exp = 220;
    Monster[30].img[0] = QImage(":/Graphics/Characters/004-Monster02.png").copy(0,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[30].img[1] = QImage(":/Graphics/Characters/004-Monster02.png").copy(64,96,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[30].alive = true;

    Monster[31].name = L"血影";
    Monster[31].hp = 99999;
    Monster[31].atk = 5000;
    Monster[31].def = 4000;
    Monster[31].boss = false;
    Monster[31].attrib = 0;
    Monster[31].gold = 0;
    Monster[31].exp = 0;
    Monster[31].img[0] = QImage(":/Graphics/Characters/011-Monster091.png").copy(0,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[31].img[1] = QImage(":/Graphics/Characters/01-Monster091.png").copy(64,32,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[31].alive = true;

    Monster[32].name = L"魔龙";
    Monster[32].hp = 99999;
    Monster[32].atk = 9999;
    Monster[32].def = 4000;
    Monster[32].boss = false;
    Monster[32].attrib = 0;
    Monster[32].gold = 0;
    Monster[32].exp = 0;
    Monster[32].img[0] = QImage(":/Graphics/Characters/011-Monster091.png").copy(0,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[32].img[1] = QImage(":/Graphics/Characters/01-Monster091.png").copy(64,0,32,32).scaled(48,48,Qt::KeepAspectRatio);
    Monster[32].alive = true;
}

BRAVER::BRAVER()
{
    status = 0;
    level = INIT_LEVEL;
    hp = INIT_HP;
    atk = INIT_ATK;
    def = INIT_DEF;
    pos_x = 9;
    pos_y = 5;
    floor = 0;
    exp = INIT_EXP;
    gold = INIT_GOLD;
    key1 = INIT_YKEY;
    key2 = INIT_BKEY;
    key3 = INIT_RKEY;
    face = 0;//0向下走，露脸；1左；2右；3向上走，漏背部
    temp_floor = 0;
    Dialog_state_num = 0;
    Whether_Press = true;
    Has_Change_Floor = false;
    Has_Cross = false;
    Summit_Cross = false;
    Has_Info = false;
    Speak_Fairy = false;
    Speak_Fairy22 = false;
    Has_Hammer = false;
    Speak_Thief = false;
    Speak_old16 = false;
    Speak_fairy_afterold = false;
    Speak_Devils16 = false;
    Speak_Devils19 = false;
    Speak_Devils21 = false;
    whether_get_magic_wand[0] = false;
    whether_get_magic_wand[1] = false;
    whether_reach_floor17 = false;
    whether_summit_magic_wand = false;
    whether_open_flourdoor = false;
    for(int i =0;i < 3;i++)
    {
        whether_improve_monster_property[i] = false;
    }
    //去过的楼层才能飞
    for(int i =0;i < FLOOR_NUM;i++)
    {
        whether_reach_floor[i] = true;
    }
    Dialog_state_num = 9;
}

floor_data::floor_data(QObject *parent) : QObject(parent)
{
    //楼梯口上楼位置，第一个数表示楼层，第二个数0代表x，1代表y
    stairs_pos[0][0] = 0;
    stairs_pos[0][1] = 5;
    stairs_pos[1][0] = 0;
    stairs_pos[1][1] = 0;
    stairs_pos[2][0] = 10;
    stairs_pos[2][1] = 0;
    stairs_pos[3][0] = 10;
    stairs_pos[3][1] = 10;
    stairs_pos[4][0] = 10;
    stairs_pos[4][1] = 0;
    stairs_pos[5][0] = 10;
    stairs_pos[5][1] = 9;
    stairs_pos[6][0] = 10;
    stairs_pos[6][1] = 4;
    stairs_pos[7][0] = 0;
    stairs_pos[7][1] = 0;
    stairs_pos[8][0] = 4;
    stairs_pos[8][1] = 6;
    stairs_pos[9][0] = 6;
    stairs_pos[9][1] = 6;
    stairs_pos[10][0] = 6;
    stairs_pos[10][1] = 5;
    stairs_pos[11][0] = 10;
    stairs_pos[11][1] = 10;
    stairs_pos[12][0] = 10;
    stairs_pos[12][1] = 0;
    stairs_pos[13][0] = 10;
    stairs_pos[13][1] = 5;
    stairs_pos[14][0] = 0;
    stairs_pos[14][1] = 5;
    stairs_pos[15][0] = 0;
    stairs_pos[15][1] = 6;
    stairs_pos[16][0] = 7;
    stairs_pos[16][1] = 5;
    stairs_pos[17][0] = 10;
    stairs_pos[17][1] = 0;
    stairs_pos[18][0] = 10;
    stairs_pos[18][1] = 10;
    stairs_pos[19][0] = 3;
    stairs_pos[19][1] = 5;
    stairs_pos[20][0] = 7;
    stairs_pos[20][1] = 5;
    stairs_pos[21][0] = 5;
    stairs_pos[21][1] = 4;

    //序章层
    int floor0[11][11]=
    {
        {1,  67, 67, 67, 67, 11, 67, 67, 67, 67, 1},
        {1 , 67, 67, 67, 67, 0,  67, 67, 67, 67, 1},
        {1 , 67, 67, 67, 67, 0,  67, 67, 67, 67, 1},
        {1 , 67, 67, 67, 67, 0,  67, 67, 67, 67,  1},
        {1 , 67, 67, 67, 67, 0,  67, 67, 67, 67,  1},
        {1 , 67, 67, 67, 67, 0,  67, 67, 67, 67,  1},
        {1 , 1,  67, 67, 67, 0,  67, 67, 67,  1,  1},
        {1 , 1,  1,  1,  1,  3,  1,  1,  1,   1, 1},
        {66, 1,  66, 1,  0,  68,  0,  1,  66,  1,  66},
        {66, 66, 66, 66, 66, 0,  66, 66, 66, 66,  66},
        {66, 66, 66, 66, 66, 0,  66, 66, 66,  66, 66},
    };
    Store_Data(0,floor0);

    //画第一层
    int floor1[11][11]=
    {
        {11,0,58,12,13,12,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,0},
        {6,0,15,3,0,1,6,58,6,1,0},
        {58,15,8,1,0,1,6,58,6,1,0},
        {1,3,1,1,0,1,1,1,14,1,0},
        {58,16,0,1,0,3,17,12,18,1,0},
        {9,0,59,1,0,1,1,1,1,1,0},
        {1,3,1,1,0,0,0,0,0,0,0},
        {0,16,0,1,1,5,1,1,1,3,1},
        {6,7,58,1,60,61,0,1,58,19,59},
        {6,57,58,1,0,10,0,1,58,58,58},
    };
    Store_Data(1,floor1);

    //第二层
    int floor2[11][11]=
    {
        {10, 1,  0,  21, 0,  1,  8,  9,  58, 60, 1},
        {0 , 1,  9,  1,  7,  1,  8,  9,  58, 59, 1},
        {0 , 1,  58, 1,  58, 1,  8,  9,  58, 20, 1},
        {0 , 1,  58, 1,  58, 1,  1,  1,  1,  3,  1},
        {0 , 1,  0,  1,  0,  0,  0,  3,  0,  0,  1},
        {0 , 1,  3,  1,  1,  3,  1,  1,  3,  1,  1},
        {0 , 62, 0,  0,  0,  0,  1,  0,  20, 0,  1},
        {0 , 1,  3,  1,  1,  4,  1,  63, 1,  63, 1},
        {0 , 1,  58, 1,  7,  6,  1,  0,  1,  0,  1},
        {0 , 1,  58, 1,  7,  6,  1,  0,  1,  0,  1},
        {11, 1,  8,  1,  7,  6,  1,  64, 1,  65, 1},
    };
    Store_Data(2,floor2);

    //第三层
    int floor3[11][11]=
    {
        {72, 13,  58, 1,  69, 70, 71, 1,  1, 1, 1},
        {13, 58,  0,  1,  0,  0,  0,  1,  0, 18, 0},
        {58, 15,  0,  1,  1,  3, 1,  1,  0, 1, 0},
        {1,  3,   1,  1,  0, 15,  0,  1,  58,  1,  13},
        {0 , 0,   0,  1,  1,  1,  0,  1,  58,  1,  18},
        {12, 1,   0,  18, 13, 18, 0,  1,  58,  1,  13},
        {12, 1,   1,  1,  1,  1,  0,  0,  0, 1,  0},
        {0 , 0,   0,  0,  0,  1,  1,  3, 1,  1, 0},
        {1 , 1,   1,  1,  18, 1,  13,  0,  13,  1,  0},
        {1 , 0,   0,  0,  0,  1,  9,  18,  58,  1,  0},
        {10, 0,   1,  1,  1,  1,  8,  7, 58,  1, 11},
    };
    Store_Data(3,floor3);

    //第四层
    int floor4[11][11]=
    {
        {0 , 14, 0,   1, 0,  78, 0,  1,  0, 14, 0},
        {3 , 1,  3,  1,  0,  0,  0,  1,  3, 1, 3},
        {0 , 1,  0 , 1,  1 , 63, 1,  1,  0, 1, 0},
        {0 , 1,  15, 1,  23, 24, 23, 1,  15,  1,  0},
        {18, 1,  6,  1,  9,  23, 9,  1,  6,  1,  18},
        {18, 1,  6,  1,  1,  5,  1,  1,  6,  1,  18},
        {13, 1 , 0,  1,  19, 22, 19, 1,  0, 1,  13},
        {13, 1,  0,  1,  8,  19, 8,  1, 0,  1, 13},
        {0 , 1,  0 , 1,  1,  4,  1,  1,  0,  1,  0},
        {0 , 1,  0 , 1,  58, 0,  58, 1,  0,  1,  0},
        {11, 1,  0 , 14, 0,  0,  0,  14, 0,  1, 10},
    };
    Store_Data(4,floor4);

    //第五层
    int floor5[11][11]=
    {
        {79, 1,  6,  1,  7,  17,  0,  0,  17, 58, 59},
        {0 , 1,  8,  1,  17, 0,   0,  0,  0, 17, 58},
        {23, 1,  0,  1,  16, 0,   1,  1,  3, 1, 1},
        {0 , 3,  17, 1,  75, 16,  1,  0,  19,  16,  65},
        {23, 1,  0,  1,  1,  1,   1,  0,  0,  0,  16},
        {8 , 1,  0,  0,  0,  18,  15, 0,  0,  0,  0},
        {9 , 1 , 1,  14, 1,  1,   1,  1,  0, 0,  0},
        {0 , 64, 1,  14, 1,  0,   0,  0, 19,  22, 0},
        {1 , 1,  1,  18, 1,  3,   1,  4,  1,  3,  1},
        {0 , 0,  1,  0,  1,  18,  1,  9,  3,  0,  1},
        {10, 0,  0,  0,  0,  0,   1,  58, 1,  11, 1},
    };
    Store_Data(5,floor5);

    //第六层
    int floor6[11][11]=
    {
        {80, 26,  1,  9, 1,   58,  28,  81,  1, 7, 7},
        {26 , 58, 1,  8,  1,  0,   58,  28,  1, 27, 7},
        {58 , 24, 4,  0,  4,  24,  0,  58,   1, 0, 27},
        {0 , 0,  1,   22,  1, 0,   0,  0,    1,  29,  0},
        {1 , 1,  1,   5,  1,  1,   1,  1,    1,  3,  1},
        {0 , 0,  25,  0,  58,  58, 58,  0,   25,  0,  0},
        {0 , 1,  1,   1,  1,  1,   1,  1,    1, 1,  1},
        {0 , 1,  23,  3,  23,  0,  0,  0,    0,  0, 1},
        {0 , 1,  3,   1,  3,  1,   1,  1,    1,  4,  1},
        {0 , 1,  23,  1,  0,  0,   1,  1,    0,  0,  1},
        {0, 0,  0,    1,  11,  0,  3,  3,    0,  10, 1},
    };
    Store_Data(6,floor6);

    //第七层
    int floor7[11][11]=
    {
        {11, 0,  0,  0,   0,  0,  0,    0,  1, 1, 1},
        {1 , 1,  0,  24,  1,  4,  1,    26,  0,1, 1},
        {1 , 0,  24, 9,   1,   30,  1,  8,  26, 0, 1},
        {0 , 0,  1,  1,   1,  63,  1,   1,  1,  0,  0},
        {0 , 0,  4,  30,  63,  82,  63, 30,  4,  0,  0},
        {0 , 1,  1,  1,   1,  63,  1,   1,  1,  1,  0},
        {0 , 1,  6,  8,   1,  30,  1,   9,  6, 1,  0},
        {0 , 1,  58,  6,  1,  4,  1,    6, 58,  1, 0},
        {0 , 1,  1,  59,  59,  0,  59,  59,  1,  1,  0},
        {0 , 0,  1,  1,   1,  5,  1,    1,  1,  0,  0},
        {1, 0,   0,  3,   10,  0,  0,   3, 0,  0, 1},
    };
    Store_Data(7,floor7);

    //第八层
    int floor8[11][11]=
    {
        {10, 1,  0,  0,  0,  0,  1, 0, 58,  26,  0},
        {0 , 1,  0,  1,  1,  3,  1, 3, 1,  1,  0},
        {0 , 1,  0,  1,  0,  0,  4, 0, 0,  1,  8},
        {0 , 1,  0,  1,  31, 1,  1, 1, 23,  1,    14},
        {23 , 1, 0,  1,  6,  1,  11, 0, 0,  1,    14},
        {24 , 1, 9,  1,  6,  1,  1, 1, 1,  1,    0},
        {23 , 1, 14, 1,  0,  0,  0,  1,0,  24,   0},
        {0 , 1,  14, 1, 1,  1,  22, 1, 3, 1,   1},
        {0 , 1,  0,  26,  0,  1,  26, 1,  0,  0,    0},
        {0 , 1,  1,  1,  3,  1,  0, 1,  1,  1,    0},
        {0, 0,   31, 0,  0,  1,  0, 28,  30, 28,   0},
    };
    Store_Data(8,floor8);

    //第九层
    int floor9[11][11]=
    {
        {83, 58,  0,  1,   1,  1,  0,  0,  0, 1, 0},
        {58 , 0,  32,  3,  0,  0,  0,  1,  0, 3, 26},
        {1 , 3,  1,    1,  0,  1,  1,  1,  0, 1, 58},
        {0 , 0,  0,   1,  0,   1,  0,  0,  0,  1,  58},
        {0 , 0,  0,   5,  0,   1,  10,  1,  0,  1,  6},
        {1 , 4,  1,   1,  0,   1,  1,  1,  0,  1,  1},
        {9 , 29, 8,   1,  31,  1,  11,  1,  0, 1,  6},
        {1 , 3,  1,   1,  0,   0,  0,  3, 0, 1, 58},
        {26 , 6,  26, 1,  1,   4,  1,  1,  0,  1,  58},
        {59 , 26,  6, 1,  27,  31,  27,  1,  0,  3,  26},
        {73, 59,  26,  3,  7,  27,  7,  1, 0,  1, 0},
    };
    Store_Data(9,floor9);

    //第十层
    int floor10[11][11]=
    {
        {0, 1,  1,   9,  32,   1,  32,   8,  1, 1, 0},
        {0 , 0,  1,  1,  3,    1,  3,    1,  1, 0, 29},
        {0 , 0,  0,  0,  0,    1,  0,    0,  0, 29, 7},
        {0 , 1,  0,  1,  1,     1,  1,   1,  0,  1,  1},
        {23 , 1,  0,  0,  58,   58,  58,  0,  0,  1,  58},
        {24 , 1,  0,  1,  1,   1,    1,  3,  1,  1,  58},
        {23 , 1, 0,  63,  0,   10,  1,  0,  3, 24,  0},
        {0 , 1,  1,  1,  1,    1,  1,   3, 1,  1, 0},
        {0 , 1,  6,  9,  8,    1,  0,   24,  0,  1,  58},
        {0 , 1,  6,  9,  8,    5,  31,  1,  31,  1,  58},
        {11, 1,  6,  9,  8,    1,  59,  1, 59,  1, 6},
    };
    Store_Data(10,floor10);

    //第十一层
    int floor11[11][11]=
    {
        {6,  1,  58,  1,  59,  1,  60,  1,  7, 76, 7},
        {6 , 1,  58,  1,  59,  1,  60,  1,  33, 34, 33},
        {6 , 1,  58,  1,  59, 1,   60,  1,  0, 33, 0},
        {3 , 1,  3,   1,  3, 1,    3,  1,  1,  4,  1},
        {0 , 0,  0,   0,  0,  1,   0,  0,  0,  0,  0},
        {3 , 1,  1,   4,  1,  1,   1,  4,  1,  1,  3},
        {9 , 1,  0,   33,  7,  35, 7,  33,  0, 1,  8},
        {9 , 1,  32,  1,  1,  1,   1,  1, 32,  1, 8},
        {9 , 1,  32,  1,  69,  70, 71,  1,  32,  1,  8},
        {1 , 1,  5,   1,  6,  0,   6,  1,  5,  1,  1},
        {10, 0,  0,   0,  0,  0,   0,  0, 0,  0, 11},
    };
    Store_Data(11,floor11);

    //第十二层
    int floor12[11][11]=
    {
        {65,  9,  1,  0,  20,  21,  20,   0,  1, 7, 84},
        {8 , 0,  1,  0,  1,    3,  1,     0,  1, 0, 7},
        {0 , 0,  1,  0,  1,   21,   1,    0,  1, 0, 0},
        {0 , 35,  1,  0,  1,   58,    1,  0,  1,  38,  0},
        {35 , 36,  1, 0,  1,   58,   1,   0,  1,  37,  38},
        {1 , 4,  1,   0,  1,   6,   1,    0,  1,  4,  1},
        {0 , 0,  0,   0,  1,   6, 1,      0,  0, 0,  0},
        {1 , 1,  1,  0,  1,    1,   1,     0, 1,  1, 1},
        {9 , 35, 3,  33, 33,  34, 33,     33,  3,  35,  8},
        {1 , 1,  1,   1,  1,  4,   1,    1,  1,  1,  1},
        {11, 0,  0,   0,  0,  0,   0,    0, 0,  0, 10},
    };
    Store_Data(12,floor12);

    //第十三层
    int floor13[11][11]=
    {
        {0, 35,  0,  0,   0,  0,    0,  1,  0, 36, 0},
        {0 , 1,  1,  1,   1,  1,    3,  1,  0, 1, 0},
        {0 , 1,  0, 0,    33, 0,    0,  1,  0, 1, 0},
        {7, 1,   5, 1,    1, 1,     0,  1,  0,  1,  0},
        {20 , 1,  0,  0,  36,  1,   33,  1,  8,  1,  0},
        {21 , 1,  0,  39,  63,  1,  34,  1,  8,  1,  0},
        {20 , 1, 36,  63,  64,  1,  33,  1,  8, 1,  9},
        {0 , 1,  1,  1,   1,  1,    0,  1, 0,  1, 9},
        {0 , 0,  0, 1,    0,  0,    0,  36,  0,  1,  9},
        {1 , 1,  0, 1,    7,  1,    1,  1,  1,  1,  0},
        {10, 0,  0,  4,   0,  11,   1,  85, 39,  3, 0},
    };
    Store_Data(13,floor13);

    //第十四层
    int floor14[11][11]=
    {
        {1,  0,  38,  79, 11,  0,  0,   0,  0, 0, 1},
        {1 , 0,  7,  1,   1,  1,  1,    1,  7, 0, 1},
        {1 , 0,  1, 1,    1,  1,  1,    1,  1, 0, 1},
        {1 , 0,  1, 1,    1,   86,  1,  1,  1,  0,  1},
        {1 , 0,  1,  1,    1,  63,  1,  1,  1,  0,  1},
        {1 , 0,  6,  1,    1,  36,  1,  1,  6,  0,  1},
        {1 , 0,  67,  67,  1,  39,  1,  67,  67, 0,  1},
        {1 , 0,  67,  67,  1,  36,  1,  67, 67,  0, 1},
        {1 , 0,  67, 67,   1,  4,  1,    67,  67,  0,  1},
        {1 , 33,  34, 33,  4, 0,  4,    33,  34, 33,  1},
        {1,  1,   1,   1,  1,  10,  1,  1,  1, 1,  1},

    };
    Store_Data(14,floor14);

    //第十五层
    int floor15[11][11]=
    {
        {0,  0,  0,   0,    10,  67,  11,  0,  0, 0, 0},
        {0 , 67,  67,  67,  67,  67,  67,  67,  67, 67, 0},
        {0 , 67,  67, 1,    1,  1,    1,  1,   67, 67, 0},
        {0 , 67,  1, 1,     64, 1,    65,  1,  1,  67,  0},
        {0 , 67,  1,  1,    9,  1,    9,  1,  1,  67,  0},
        {0 , 67,  1,  1,    8,  1,    8,  1,  1,  67,  0},
        {0 , 67,  67,  1,   0,  1,    0,  1,  67, 67,  0},
        {0 , 67,  67,  1,   3,  1,    3,  1,   67,  67, 0},
        {0 , 67,  67, 67,   0,  0,    0,  67,  67,  67,  0},
        {0 , 67,  67, 67,   67,  5,    67,  67,  67,  67,  0},
        {0, 0 ,  0,  0,     0,  0,    0,  0,   0,  0, 0},
    };
    Store_Data(15,floor15);

    //第十六层
    int floor16[11][11]=
    {
        {67, 67,  67,  67,  67,  0,  10,  67,  67, 67, 67},
        {67 , 67,  67, 67,  67,  0,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  67,  0,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  1,   0,  1,  67,  67,  67,  67},
        {67 , 67,  67,  1,  64,  0,  1,  1,  67,  67,  67},
        {67 , 67,  67,  1,  1,  40,  1,  1,  67,  67,  67},
        {67 , 67, 67,  1,   1,  0,  1,  1,  67, 67,  67},
        {67 , 67,  67,  1,  1,  11,  1,  1, 67,  67, 67},
        {67 , 67,  67, 67,  1,  1,  1,  67,  67,  67,  67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67,  67,  67},
        {67, 67,  67,  67,  67,  67,  67,  67, 67,  67, 67},
    };
    Store_Data(16,floor16);

    //第十七层
    int floor17[11][11]=
    {
        {67, 38,  39,  0,    0,   0,  0,    0,  0, 0, 38},
        {67 , 39,  67,  67,  67,  67,  67,  67,  67, 67, 0},
        {67 , 0,  67, 38,    0,   0,  0,    0,  0, 0, 38},
        {67 , 0,  67, 0,     67,  67,  67,  67,  67,  67,  67},
        {67 , 0,  67,  0,    67,  38,  0,   0,  0,  38,  67},
        {67 , 0,  67,  38,   0,   0,  67,   67,  67,  0,  67},
        {67 , 0,  67,  67,   67,  67,  67,  38,  0, 38,  67},
        {67 , 39, 67,  67,   67,  10,  67,  0, 67,  67, 67},
        {67 , 38, 39, 0,     41,  0,  67,    38,  0,  0,  38},
        {67 , 67, 67, 67,    67,  67,  67,   67,  67, 67,  0},
        {11, 0,    41,  0,   0,  0,  0,  0,  0,  0, 38},
    };
    Store_Data(17,floor17);

    //第十八层
    int floor18[11][11]=
    {
        {67, 67,  67,  67,  67,  67,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  1,   1,  1,  67,  67,  67,  67},
        {67 , 67,  67,  1,  1,  87,  1,  1,  67,  67,  67},
        {67 , 67,  67,  1,  1,  63,  1,  1,  67,  67,  67},
        {67 , 67, 67,  1,   1,  5,  1,  1,  67, 67,  67},
        {67 , 67,  67,  67,  1,  5,  1,  67, 67,  67, 67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67,  67,  67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67,  67,  67},
        {10, 0,  0,  0,  0,  0,  0,  0, 0,  0, 0},
    };
    Store_Data(18,floor18);

    //第十九层
    int floor19[11][11]=
    {
        {0, 0,    0,  0,   0,    0,  0,  0,  0, 0, 0},
        {0 , 67,  0,  67,  67,   67,  67,  67,  0, 67, 0},
        {0 , 67,  0, 67,  67,    67,  67,  67,  0, 67, 0},
        {0 , 67,  0, 67,  67,    11,  67,  67,  0,  67,  0},
        {0 , 67,  0,  67,  67,   0,  67,  67,  0,  67,  0},
        {0 , 67,  40,  67,  67,  0,  67,  67,  40,  67,  0},
        {0 , 67,  63,  67,  67,  42,  67,  67,  63, 67,  0},
        {0 , 67,  74,  67,  67,  0,  67,  67, 77,  67, 0},
        {0 , 67,  67, 67,  67,   0,  67,  67,  67,  67,  0},
        {0 , 67,  67, 67,  67,   0,  67,  67,  67,  67,  0},
        {0,   0,  0,  0,  0,  0,  0,  0, 0,  0, 10},
    };
    Store_Data(19,floor19);

    //第二十层
    int floor20[11][11]=
    {
        {41, 8,  30,  6,    39,  60, 39,   6 , 30, 8, 41},
        {7 , 67,  58,  67,  59,  67,  59,  67,  58, 67, 7},
        {67 , 9,  30, 0,    38, 0,  38,    0,  30, 9, 67},
        {6 , 67,  58, 67,   0, 10,  0,    67,  58,  67,  6},
        {39 , 59,  38,  0,  0,  0,  0,    0,  38,  59,  39},
        {60 , 67,  0,  67,  0,  67,  0,  67,  0,  67,  60},
        {39 , 59, 38,  0,   0,  0,  0,    0,  38, 59,  39},
        {6 , 67,  58,  67,  0,  11,  0,    67, 58,  67, 6},
        {67 , 9,  30, 0,    38,  0,  38,  0,  30,  9,  67},
        {7 , 67,  58, 67,   59,  67,  59,  67,  58,  67,  7},
        {41, 8,  30,  6,   39,  60,  39,  6, 30,  8, 41},
    };
    Store_Data(20,floor20);

    //第二十一层
    int floor21[11][11]=
    {
        {67, 67,  67,  67,  67,  11,  67,  67,  67, 67, 67},
        {67 , 67,  0, 0,  67,  42,  67,  0,  0, 67, 67},
        {67 , 0,  0, 67,  67,  37,  67,  67,  0, 0, 67},
        {67 , 0,  0, 0,  67,   37,  67,  0,  0,  0,  67},
        {67 , 67,  0,  0,  0,  0,  0,  0,  0,  67,  67},
        {67 , 67,  0,  0,  0,  0,  0,  0,  0,  67,  67},
        {67 , 67, 67,  0,   0,  67,  0,  0,  67, 67,  67},
        {67 , 67,  67,  67,  63,  10,  63,  67, 67,  67, 67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67,  67,  67},
        {67 , 67,  67, 67,  67,  67,  67,  67,  67,  67,  67},
        {67, 67,  67,  67,  67,  67,  67,  67, 67,  67, 67},
    };
    Store_Data(21,floor21);

    //第二十二层
    int floor22[11][11]=
    {
        {67, 67,  67,  67,  67,  10,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  67,  0,  67,  67,  67, 67, 67},
        {67 , 67,  67, 67,  0,  0,  68,  67,  67, 67, 67},
        {63 , 63,  63, 67,  67,  5,  67,  67,  63,  63,  63},
        {8 , 8,  63,   67,  67,  81,  67,  67,  63,  9,  9},
        {11 , 8,  38,  5,    81,  0,  81,  5,  38,  9,  11},
        {8 , 8, 63,    67,   67,  81,  67,  67,  63, 9,  9},
        {63 , 63,  63,  67,  67,  5,  67,  67, 63,  63, 63},
        {67 , 67,  67, 63,  63,  38,  63,  63,  67,  67,  67},
        {67 , 67,  67, 63,  7,  7,    7,  63,  67,  67,  67},
        {67, 67,  67,  63,  7,  11,    7,  63, 67,  67, 67},
    };
    Store_Data(22,floor22);

    //第二十三（左）层
    int floor23[11][11]=
    {
        {38, 0,  0,     8,    8,    8,    0,  0,  67, 0, 7},
        {0 , 67,  67,   67,   67,    67,  67,  0,    4, 0, 67},
        {8 , 67,  67,   37,  38,   38,    38,  0,  67, 0, 67},
        {8 , 67,  67,   80,  67,   67,    67,  67,  67,  0,  67},
        {0 , 37,  67,    67,  67,  67,    67,  67,  81,  0,  67},
        {67 , 5,  42,   63,  88,  67,    67,  81,  4,  0,  10},
        {0 , 37, 67,   67,  67,  67,    67,  67,  81, 0,  67},
        {8 , 67,  67,   80,  67,  67,    67,  67,  67,  0, 67},
        {8 , 67,  67,   37,  38,  38,    38,  0,  67,  0,  67},
        {0 , 67,  67,   67,  67,  67,    67,  0,   4,  0,  67},
        {38, 0,  0,     8,    8,  8,     0,  0,   67,  0, 7},
    };
    Store_Data(23,floor23);

    //第二十三（右）层
    int floor24[11][11]=
    {
        {7,    0,  67,     0,    0,    0,    9,  9,  9, 0, 38},
        {67 , 0,  4,   0,       67,    67,  67,  67,  67, 67, 0},
        {67 , 0,  67,   0,     38,   38,    38,  37,  67, 67, 9},
        {67 , 0,  67,   67,    67,   67,    67,  80,  67,  67,  9},
        {67 , 0,  81,    67,   67,  67,    67,  67,  67,  37,  0},
        {10 , 0,  4,   81,    67,  67,    89,  63,  42,  4,  67},
        {67 , 0, 81,   67,    67,  67,    67,  67,  67, 37,  0},
        {67 , 0,  67,   67,   67,  67,    67,  80,  67,  67, 9},
        {67 , 0,  67,   0,    38,  38,    38,  37,  67,  67,  9},
        {67 , 0,  4,   0,     67,  67,    67,  67,   67,  67,  0},
        {7, 0,  67,     0,     0,  0,     9,  9,   9,  0, 38},
    };
    Store_Data(24,floor24);

    //第二十三（下）层
    int floor25[11][11]=
    {
        {7, 67,  67,  67,  67,  10,  67,  67,  67, 67, 7},
        {0 , 0,  0,   0,   0,    0,  0,  0,    0, 0, 0},
        {67 , 4,  67, 67,  79,   4,  79,  67,  67, 4, 67},
        {0 , 0,  0,   67,  67,   79,  67,  67,  0,  0,  0},
        {0 , 67,  38, 67,  67,  67,  67,  67,  38,  67,  0},
        {0 , 67,  38, 67,  67,  67,  67,  67,  38,  67,  0},
        {6 , 67, 38,  67,  67,  62,  67,  67,  38, 67,  6},
        {6 , 67,  37, 85,  67,  63,  67,  85,  37,  67, 6},
        {6 , 67,  67, 67,  67,  42,  67,  67,  67,  67,  6},
        {0 , 67,  67, 67,  37,  5,  37,  67,   67,  67,  0},
        {38, 0,  7,   7,    0,  67,  0,  7,   7,  0, 38},
    };
    Store_Data(25,floor25);

    //第二十四（章鱼）层
    int floor26[11][11]=
    {
        {66, 66,  66,  63,  63,  63,  63,  63,  66, 66, 66},
        {66 , 66,  66, 63,  0,  0,  0,  63,  66, 66, 66},
        {66 , 66,  66, 63,  0,  43,  0,  63,  66 ,66, 66},
        {66 , 66, 66,   63,  0,   0,  0,  63, 66, 66,  66},
        {66 , 66,  66,  63,  63,  0,  63,  63,  66,  66,  66},
        {66 , 7,  7,   7,    7,  37,  7,  7,  7,  7,  66},
        {66 , 66, 66,   66,   66,  38,  66,  66,  66, 66,  66},
        {66 , 66,  66,  85,  38,  42,  38,  85, 66,  66, 66},
        {66 , 66,  66, 66,  66,  38,  66,  66,  66,  66,  66},
        {66 , 66,  66, 66,  7,  37,  7,  66,  66,  66,  66},
        {66, 66,  66,  66,  66,  0,  66,  66, 66,  66, 66},
    };
    Store_Data(26,floor26);

    //第二十四（魔龙）层
    int floor27[11][11]=
    {
        {66, 66,  66,  63,  63,  63,  63,  63,  66, 66, 66},
        {66 , 66,  66, 63, 0,  0,  0,  63,  66, 66, 66},
        {66 , 66,  66, 63,  0,  44,  0,  63,  66 ,66, 66},
        {66 , 66, 66,   63,  0,   0,  0,  63, 66, 66,  66},
        {66 , 66,  66,  63,  63,  0,  63,  63,  66,  66,  66},
        {66 , 7,  7,   7,    7,  37,  7,  7,  7,  7,  66},
        {66 , 66, 66,   66,   66,  38,  66,  66,  66, 66,  66},
        {66 , 66,  66,  85,  38,  42,  38,  85, 66,  66, 66},
        {66 , 66,  66, 66,  66,  38,  66,  66,  66,  66,  66},
        {66 , 66,  66, 66,  7,  37,  7,  66,  66,  66,  66},
        {66, 66,  66,  66,  66,  0,  66,  66, 66,  66, 66},
    };
    Store_Data(27,floor27);
}

void floor_data::Store_Data(int k,int floor[11][11])
{
    QVector<QVector<int>> v;
    for(int i = 0; i < 11; i++)
    {
        QVector<int> v1;
        for(int j =0 ; j < 11; j++)
        {
            v1.push_back(floor[i][j]);
        }
        v.push_back(v1);
    }
    Floor.insert(k+1,v);
    v.clear();
    for(int i =0; i < 11; i++)
    {
        for(int j =0; j < 11; j++)
        {
            floor_array[k][i][j] = floor[i][j];
        }
    }
}
