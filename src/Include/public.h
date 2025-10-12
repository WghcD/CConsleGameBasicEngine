#pragma once
#define flow isflow
#define DEBUG Debug
#define debug Debug
#define HIGH 147
#define WIDE 61
#define LL long long
#include"Memory.h"
#include“include.h”
using Func = std::function<void()>;
bool clear_buffer=true;//决定是否清理输入缓冲
bool noC=true;
bool allow_auto_create_entity=true;//是否允许自然生成

int map_now;//当前使用的地图在图库中的编号
const int BaseRunSpeed=20;
int state_game=0;
int GameHard=1;//游戏基准难度
bool isRunning=0;//是否正在运行
#define START 0
#define MAINMAP 1
#define FIGHT 2 
int Mode=START;
int die_number;//累计死亡次数 存档
int boss_blood[1001];
bool die_now=0;
bool init_skill_now=false;
int last_tec_entity; 

char** buffer=NULL;

int hornor[11]={
	0,//
	0,//到达10层
	0,//死亡x100
	0,//
	0,//
	0,//
	0,//
	0,//
	0,//BOSS[1]
	0,//BOSS[2]
	0,//Chaos
};

int snow_color[5] = { 11,3,1,11,0 };
int storm_color[5] = { 14,6,8,4,14 };

double RES_pl;//玩家抗性

int MAIN;//主循环速度

bool map_first=0;//地图是否为刚刚新生成

bool through_wall=0;//玩家是否无视墙壁硬度

int hit_pl=15;
int level_pl=0;//玩家初始等级

bool FALL=true;//是否有重力

bool win=false;

int pass=0;//已通过层数
bool pass_now=0;



int last_check_pos=0;

int last_create_win=0;

const char player_look = '@';

int boss_create_type=0;
int boss_create_HP=0;

int last_main;

int item_now;
double HP_pl_start = 20;//血量此处
double last_entity_pl_HP=HP_pl_start;
double HP_pl = HP_pl_start;

double EHP_pl_largest=0;//伤害吸收
double EHP_pl=EHP_pl_largest;
bool Debug = true;//是否为DEBUG模式

int OP_pl=100;
bool is_move=0;
bool is_fall=true;

char der_pl = 's';//玩家方向

int entity_max_now=0;

int last_deal_flow=0;

int hp_tmp;

int last_deal_trap=0;

int entity_number,tec_entity_number,bullet_number,map_tec_entity_and_NPC_number;

int speed_player=110;//默认速度
#define speed_pl speed_player

HANDLE conhandle;
void gto(int x, int y) {
	if(x<0||y<0){gto(0,0);}
	COORD pos; pos.X = 2*y; pos.Y = 2*x;
	SetConsoleCursorPosition(conhandle, pos);
}


struct point{
	int x,y;
	point(int x,int y){this->x=x,this->y=y;}
};

struct Entity_infor {
	
	int dHP = 0,HP=0;
	int nx=0,ny=0;
	int buff_time[20];
	int hit = 0;
	int type;
	int isExist = 0;
	int infoN;
	int number1;
	
};


Entity_infor bullet_map[62][157];//实体碰撞使用
/*
bool set_box(int x,int y,int HP){//创建箱
	if(x<=0||y<=0){return false;}
	if(EntityMap[x][y].isExist)return false;
	EntityMap[x][y].isExist=1;
	EntityMap[x][y].HP=HP;
	return true;
}

int deal_box(int x,int y,int lastHP){//处理箱
	if(x<=0||y<=0){return lastHP;}
	if(!EntityMap[x][y].isExist)return lastHP;
	int result=EntityMap[x][y].HP-lastHP;
	return result;
}

void destory_box(int x,int y){//销毁箱
	if(x<=0||y<=0){return;}
	EntityMap[x][y].isExist=0;
	EntityMap[x][y].HP=0;
	EntityMap[x][y].type=0;
	EntityMap[x][y].hit=0;
}*/


int color_1[5] = { 4,8,12,8,8 };
int color_2[5] = { 12,13,4,4,4 };


void show_cursor(){    CONSOLE_CURSOR_INFO cursorInfo = {1, true ? TRUE : FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);}
void hide_cursor(){HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);CONSOLE_CURSOR_INFO cursor_info = {1, 0}; GetConsoleCursorInfo(hOut, &cursor_info); cursor_info.bVisible = FALSE;SetConsoleCursorInfo(hOut, &cursor_info);}


void clear_entity(int type_tmp, int x, int y) {
	if (type_tmp == -2) { gto(x, y - 1); printf("      "); gto(x - 1, x); printf("  "); gto(x + 1, x); printf("  "); }
	if (type_tmp == -1) { gto(x, y); printf("  "); }
	if (type_tmp == 1) { gto(x, y); printf("   "); gto(x, y - 3); printf("    "); gto(x - 1, y - 4); printf("      "); gto(x + 1, y - 4); printf("        "); }
	if (type_tmp == 2) { gto(x, y); printf("         "); gto(x, y - 4); printf("    "); gto(x - 1, y); printf("  "); gto(x + 1, y); printf("  "); gto(x + 2, y); printf("  "); }
}






void SetColor_p(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
int derX(char der,int x){if(der=='w')return x-1;else if(der=='s')return x+1;return x;}
int derY(char der,int y){if(der=='a')return y-1;else if(der=='d')return y+1;return y;}

int der_deal_y(char der, int y) {
	if (der == 'q') y--;
	if (der == 'x') y++;
	if (der == 'z') y--;
	if (der == 'e') y++;

	if (der == 'a')y--;

	if (der == 'd')y++;
	return y;
}

int der_deal_x(char der, int x) {
	
	if (der == 'q')x--;
	if (der == 'x')x++;
	if (der == 'z')x++;
	if (der == 'e')x--;
	if(FALL)
	if (der == 'w')x-=2;
	
	
	if(FALL==0){
		if(der=='s'){x++;}
		if (der == 'w')x-=1;
	}

	return x;
}

int dder_deal_x(char der, int x) {
	
	if (der == 'q')x--;
	if (der == 'x')x++;
	if (der == 'z')x++;
	if (der == 'e')x--;
	if (der == 'w')x--;
	if (der == 's')x++;
	
	

	return x;
}

void no(){int a=0;}//这个函数用于给函数指针留空

#define point_is_legal point_is_allowed
bool point_is_legal(int x,int y){
	if(x<=WIDE&&y<=HIGH&&x>=1&&y>=1)return true;
	else return false;
}








