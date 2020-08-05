#ifndef VARIABLES_H
#define VARIABLES_H
#include <iostream>
#include <QString>
#include <QImage>
#include <QObject>
#include <QMap>
#include <QVector>
#include <string>
#include <QTimer>

using namespace std;

#define MONSTER_NUM 33 //怪物的数量
#define FLOOR_NUM 27 //楼层数
#define INIT_LEVEL 1
#define INIT_HP 1000
#define INIT_ATK 10
#define INIT_DEF 10
#define INIT_EXP 0
#define INIT_GOLD 0
#define INIT_YKEY 10
#define INIT_BKEY 10
#define INIT_RKEY 10

#define FIGHT_INTERVAL 200 //战斗掉血时间间隔
#define GOLD_EXP_INTERVAL 500//显示获得金币经验间隔
#define VICTORY_INTERVAL 300//获胜图片存在时间
#define TEXT_INTERVAL 30 //文字上滑间隔
#define MAX_FLOOR_NUM 27 //测试用，防止新一层没做触发上楼引起崩溃
#define GRADUAL_CHANGE_INTERVAL 1000//渐变动画间隔
#define CURRENT_FLOOR_NUM 1//当前层数，方便测试用

#define IMG_BRAVE_PATH ":/Graphics/Characters/002-Braver01.png" //勇士图片路径, 更换勇士图片用



struct MONSTER
{
    int hp; //血量
    int atk; //攻击力
    int def; //防御力
    int attrib; //怪物属性，如中毒/先攻等
    int exp; //经验值
    int gold; //金币
    bool boss; //是否为boss
    bool alive;//当前层是否还有次怪物
    wstring name; //怪物名称
    QImage img[2];
};

class BRAVER
{
public:
    int status; //状态
    int level; //等级
    int hp; //血量
    int atk; //攻击力
    int def; //防御力
    int pos_x; //当前x位置
    int pos_y; //当前y位置
    int floor; //当前层数
    int exp; //经验值
    int gold; //金币
    int key1; //钥匙1
    int key2; //钥匙2
    int key3; //钥匙3
    int face; //朝向
    int temp_floor;//存储要飞的楼层号
    bool Whether_Press;//当触发特效时，勇士不能进行按键操作
    bool Has_Change_Floor;//有跳楼器
    bool Has_Cross;//是否有十字架
    bool Summit_Cross;//是否将十字架给了仙女
    bool Has_Info;//是否有查看信息
    bool Speak_Fairy;//是否和仙子对过话
    bool Speak_Fairy22;//是否和22仙子首次说话
    bool Has_Hammer;//是否拥有榔头
    bool Speak_Thief;//是否和小偷对过话
    bool Speak_old16;//是否和16楼老头说过话
    bool Speak_fairy_afterold;//和16楼老头对过话后和仙子对过话
    bool Speak_Devils16;//和16楼魔王对话
    bool Speak_Devils19;//和19楼魔王对话
    bool Speak_Devils21;//和21楼魔王对话
    bool whether_open_flourdoor;//是否打开23层花门(是打血影，不是打魔龙)
    bool whether_get_magic_wand[2];//是否集齐三根魔杖
    bool whether_summit_magic_wand;//是否提交魔杖
    bool whether_reach_floor[FLOOR_NUM];//是否去过这一层，去了才能飞，
    bool whether_reach_floor17;//是否去过这一层,去了17楼怪物属性增强
    bool whether_improve_monster_property[3];//是否提升过怪物属性，序号代表第几次提升

    int Dialog_state_num;//对话框状态数字，每个数字代表一个对话框,0:首次和仙女对话。1：拿到十字架后和仙女对话。2：和2楼老头对话。3：和2楼商人对话4：首次和小偷对话
    //5:拿宝石后和小偷对话。6:5楼老头经验商店。 7:5楼商人钥匙商店。8:3楼金币商店 9:关闭游戏开始界面文字框 10:11楼金币商店 11:跳楼器 12：和12楼商人 13：13楼经验商人
    //14:15楼老头 15:15楼商人 16:16楼老头对完话和仙子对话 17:16楼老头对话 18:16楼魔王对话 19： 19楼魔王对话 20:和公主对话 21：红衣魔王死后对话 22:19层冥灵魔王死后对话
    //23 ：21魔王死后对话 24:首次和22楼仙女对话。25:集齐灵杖后和仙女对话

    //保存游戏用存储当前状态
    int save_status; //状态
    int save_level; //等级
    int save_hp; //血量
    int save_atk; //攻击力
    int save_def; //防御力
    int save_pos_x; //当前x位置
    int save_pos_y; //当前y位置
    int save_floor; //当前层数
    int save_exp; //经验值
    int save_gold; //金币
    int save_key1; //钥匙1
    int save_key2; //钥匙2
    int save_key3; //钥匙3
    int save_face; //朝向
    int save_temp_floor;
    bool save_Whether_Press;//当触发特效时，勇士不能进行按键操作
    bool save_Has_Change_Floor;//有跳楼器
    bool save_Has_Cross;//是否有十字架
    bool save_Summit_Cross;//是否将十字架给了仙女
    bool save_Has_Info;//是否有查看信息
    bool save_Speak_Fairy;//是否和仙子对过话
    bool save_Speak_Fairy22;//是否和22仙子首次说话
    bool save_Has_Hammer;//是否拥有榔头
    bool save_Speak_Thief;//是否和小偷对过话
    bool save_Speak_old16;//是否和16楼老头说过话
    bool save_Speak_fairy_afterold;//和16楼老头对过话后和仙子对过话
    bool save_Speak_Devils16;//和16楼魔王对话
    bool save_Speak_Devils19;//和19楼魔王对话
    bool save_Speak_Devils21;//和21楼魔王对话
    bool save_whether_open_flourdoor;//是否打开23层花门(是打血影，不是打魔龙)
    bool save_whether_get_magic_wand[2];//是否集齐三根魔杖
    bool save_whether_summit_magic_wand;//是否提交魔杖
    bool save_whether_reach_floor[FLOOR_NUM];//是否去过这一层，去了才能飞，
    bool save_whether_reach_floor17;//是否去过这一层,去了17楼怪物属性增强
    bool save_whether_improve_monster_property[3];//是否提升过怪物属性，序号代表第几次提升
    int save_Dialog_state_num;//状态
    int save_floor_num;//保存时所处楼层
    BRAVER();
};

class floor_data : public QObject
{
    Q_OBJECT
public:
    explicit floor_data(QObject *parent = 0);

public:

    QMap<int, QVector< QVector<int> > >Floor;//存放地图数据，key存放楼层数（比实际大1），value存放每一层对应信息
    int floor_array[FLOOR_NUM][11][11];//保存最初地图状态，重启游戏用
    int floor_save[FLOOR_NUM][11][11];//保存游戏用，存储当前游戏状态
    void Store_Data(int k,int floor[11][11]);//存放数据用函数,k是当前楼层
    int stairs_pos[FLOOR_NUM][4];//存放每层楼楼梯口位置,0:上楼x坐标1：上楼y，2：下楼x，3：下楼y
signals:

public slots:

};

extern MONSTER Monster[MONSTER_NUM]; //怪物的信息
extern BRAVER Braver;//勇者信息
extern floor_data floor;

extern vector<int> vtemp;//全局数组，存放当前地图已存活怪物序号
extern QTimer* extern_timer;
void init_monsters(); //初始化全局变量




#endif // VARIABLES_H
