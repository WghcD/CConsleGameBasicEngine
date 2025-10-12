#pragma once



#include"head.h"



#define NOTUPDATE 534653

queue<std::function<void()>> EntityUpdateQueue;


class ENTITYINFO;
class ENTITYINFO{//存储一切实体基本数据  可通过已知entity编号情况下进行统一的SetPosition等操作
	public:
	int* px,*py,*pHP;double *pDamageMulti;
	bool isUsed=0;
	function<void()> pchangePosition=nullptr;
};

class Entity;
class Entity{
public:
	int HP,x,y,lx,ly,speed=0,dspeed;
	int lastUpdate=0,lastFall;
	bool isExist,NoInfluenceFromMap=0,noFall=0;
	double DamageMulti=1;

	int infoN;
	Entity();
	bool set_box();
	int deal_box();
	bool destory_box();
	bool attackEntity(int x,int y,int value,int type);
	void setSpeed(int speed);
	void changeSpeed(int speed);
	int setHealth(int newHP);
	int changeHealth(int dHP,int type);
	void setPostion(int newx,int newy);
	bool blockOk();
	int entity_map_deal();
	bool fall();
	int getX();
	int getY();
	virtual void show();
	virtual void clear();
	virtual void update();
	void Update();
	bool positionCheck();
	void changePosition(int dx,int dy);
	void destory();
	void recordInfo();
	void putUpdate();
	bool speedCheck();
	int entity_general_deal(int n);
};




class ParabolaEntity:public Entity;
class ParabolaEntity:public Entity//遵循抛物线  指定初始动量及角度的物体
{
	public:
	int n;
	char look='X';
	Force f;
	void show();
	void clear();
	void init(int X,int Y,double xF,double yF);
	void init(int X,int Y,int n,double F,double angle);
	void update();
};
class TRACK_BULLET:public Entity;
class TRACK_BULLET:public Entity
{
	public:
	char look='A';
	int energy;
	int *nx,*ny;//指向受跟踪目标的坐标
	void show();
	void clear();
    void init(int x,int y,int &Nx,int &Ny,int speed);
	void update();
};

class PLAYER:public Entity;
class PLAYER:public Entity
{
	public:
	int itemNow,skillNow,isHit,isDie;
	void init();
	void show();
	void clear();
	void update();
};


class DOOR:public Entity;
class DOOR:public Entity
{//传送门  成对的门是一个实体
public:
	int sx,sy,tx,ty,backgroundColor,color;
	string slook,tlook;
	void init(int sx,int sy,int tx,int ty,int color,int bkColor,string slook,string tlook);
	void init(int sx,int sy,int tx,int ty);
	void show();
	void clear();
	void update();
};
class EldritchHorror:public Entity;
class EldritchHorror:public Entity
{
public:
	void MengYan();
	void RemoveMengYan();
	void show();
	void update();
};


































































