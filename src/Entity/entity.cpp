#pragma once
#include"entity.h"
#include"entityFunc.cpp"


#define NOTUPDATE 534653

queue<std::function<void()>> EntityUpdateQueue;



class ENTITYINFO{//存储一切实体基本数据  可通过已知entity编号情况下进行统一的SetPosition等操作
	public:
	int* px,*py,*pHP;double *pDamageMulti;
	bool isUsed=0;
	function<void()> pchangePosition=nullptr;
};

vector<ENTITYINFO> EntityInfo(10001);
class Entity{
public:
	int HP,x,y,lx,ly,speed=0,dspeed;
	int lastUpdate=0,lastFall;
	bool isExist,NoInfluenceFromMap=0,noFall=0;
	double DamageMulti=1;

	int infoN;
	Entity(){infoN=get_rand(1,10000);}
	bool set_box(){
		if(!point_is_legal(x,y))return false;
		if(EntityMap[x][y].isExist)return false;
		EntityMap[x][y].isExist=1;EntityMap[x][y].HP=HP;EntityMap[x][y].infoN=infoN;
		return true;
	}
	int deal_box(){
		if(!point_is_legal(x,y))return 0;
		if(!EntityMap[x][y].isExist)return 0;
		if(EntityMap[x][y].dHP!=0){//接收伤害
		changeHealth(EntityMap[x][y].dHP,EntityMap[x][y].type);}
		if(EntityMap[x][y].nx!=0||EntityMap[x][y].ny!=0){
		x=EntityMap[x][y].nx,y=EntityMap[x][y].ny;gto(0,0); /*接收位移  用于传送门等*/}
		return EntityMap[x][y].dHP;
	}
	bool destory_box(){
		if(!point_is_legal(x,y))return false;
		if(!EntityMap[x][y].isExist)return false;
		EntityMap[x][y].isExist=0;EntityMap[x][y].HP=0;EntityMap[x][y].infoN=0;
		return true;
	}
	bool attackEntity(int x,int y,int value,int type){if(!EntityMap[x][y].isExist){return false;}EntityMap[x][y].dHP=-value;EntityMap[x][y].type=type;return true;}//对指定位置可能存在的实体造成一次伤害
	void setSpeed(int speed){this->speed=speed;}
	void changeSpeed(int speed){this->speed+=speed;}
	int setHealth(int newHP){HP=newHP;return HP;}
	int changeHealth(int dHP,int type){
		if(dHP<0){//受到伤害
		if(type==0){HP+=dHP;}//强制伤害
		if(type==1){HP+=dHP*DamageMulti;}//常规伤害
		}else HP+=dHP;
		return HP;
	}
	void setPostion(int newx,int newy){
		deal_box();
		destory_box();
		x=newx,y=newy;
		set_box();
	}
	bool blockOk(){if(GameMap->block[x][y].hard<=0&&(!EntityMap[x][y].isExist))return 1;else return 0;}
	int entity_map_deal(){
		fall();
		if(NoInfluenceFromMap){return -1;}
		HP+=GameMap->block[x][y].dHP;
		if(GameMap->block[x][y].hard>0){x=lx,y=ly;return 1;}
		else return 0;
	}
	bool fall(){
		if(noFall)return 0;
		if(clock()-lastFall>500&&GameMap->getHard(x+1,y)<=0){x++;return 1;}
		return 0;
	}
	int getX(){return x;}
	int getY(){return y;}
	virtual void show(){}
	virtual void clear(){}
	virtual void update(){}
	void Update(){update();}
	bool positionCheck(){if(x<=1||y<=1||x>=HIGH||y>=WIDE){return false;}return true;}
	void changePosition(int dx,int dy){
		clear();
		int newx=dx+x,newy=y+dy;
		setPostion(newx,newy);
	}
	void destory(){clear();destory_box();HP=0;x=HIGH/2;y=WIDE/2;isExist=0;EntityInfo[infoN].isUsed=0;}
	void recordInfo(){lx=x,ly=y;EntityInfo[infoN].isUsed=1;EntityInfo[infoN].px=&x,EntityInfo[infoN].py=&y,EntityInfo[infoN].pHP=&HP,EntityInfo[infoN].pDamageMulti=&DamageMulti;}
	void putUpdate(){if(!isExist){return;}EntityUpdateQueue.push(std::bind(&Entity::update, this));}
	bool speedCheck(){dspeed=BaseRunSpeed-MAIN;/*速度校正*/ if(clock()-lastUpdate>speed+dspeed){lastUpdate=clock();return 1;} return 0;}
	int entity_general_deal(int n){
		
		if(n==0){
		if(!speedCheck()){putUpdate();return NOTUPDATE;}
		recordInfo();
		clear();
		int DHP=deal_box();
		destory_box();
		return DHP;
		}else{
		entity_map_deal();
		if(!positionCheck()){if(x<0)x=1;if(y<0)y=1;if(x>WIDE)x=WIDE-1;if(y>HIGH)y=HIGH-1;}
		set_box();
		show();
		putUpdate();
		}
		return 0;
	}
};

void entity_update(){
	while(!EntityUpdateQueue.empty()){
		EntityUpdateQueue.front()();//执行update()
		EntityUpdateQueue.pop();
	}
    
}


#define PE ParabolaEntity
class ParabolaEntity:public Entity//遵循抛物线  指定初始动量及角度的物体
{
	public:
	int n;
	char look='X';
	Force f;
	void show(){
		gto(x,y);cout<<look;
	}
	void clear(){
		show_char(x,y);
	}
	void init(int X,int Y,double xF,double yF){isExist=1;x=X;y=Y;f.init(xF,yF);update();speed=500;}
	void init(int X,int Y,int n,double F,double angle){isExist=1;x=X;y=Y;f.init(angle,F,n);update();speed=500;}
	void update(){
		if(!speedCheck()){putUpdate();return;}
		gto(0,0);cout<<"Update Successfully! Times:"<<n++;
		recordInfo();
		clear();
		x+=f.xF,y+=f.yF;
		f.xF-=G;f.yF-=0.1;
		if(!positionCheck()){destory();/*gto(3,0);cout<<"Destroyed";*/}
		show();
		putUpdate();
	}
};
#define TB TRACK_BULLET
class TRACK_BULLET:public Entity
{
	public:
	char look='A';
	int energy;
	int *nx,*ny;//指向受跟踪目标的坐标
	void show(){gto(x,y);printf("%c",look);}
	void clear(){print_char(x,y);}
    void init(int x,int y,int &Nx,int &Ny,int speed){nx=&Nx;ny=&Ny;this->speed=speed;this->x=x;this->y=y;isExist=1;update();}
	void update(){
		if(!speedCheck()){putUpdate();return;}
		recordInfo();
		clear();
		if(deal_box()<0){destory();};
		destory_box();
		int X=abs(*nx-x),Y=abs(*ny-y);
		if(get_rand(1,X)>=get_rand(1,Y)){
			if(*nx>x){x++;}else x--;
		}else{if(*ny>y){y++;}else y--;}
		
		if(!positionCheck()){destory();}
		set_box();
		show();
		putUpdate();
	}
};


class PLAYER:public Entity
{
	public:
	int itemNow,skillNow,isHit,isDie;
	void init(){
		isExist=1;
		x=WIDE/2,y=HIGH/2;
		speed=speed_pl;
		update();
	}
	void show(){
		gto(x,y);if(isHit){Color(4,16);}else{Color(2,16);}printf("@");COLOR isHit=0;
	}
	void clear(){
		print_char(x,y);
	}
	void update(){
		
		int update_result=entity_general_deal(0);
		if(update_result<0){isHit=1;};
		if(update_result==NOTUPDATE){gto(4,0);cout<<lastUpdate;return;}

		
		
		char Input=input();
		if(Input=='w'&&noFall)x--;if(Input=='w'&&!noFall&&GameMap->getHard(x-1,y)<=0){x-=2;}if(Input=='s'&&!noFall)x++;if(Input=='a')y--;if(Input=='d')y++;
		
		
		entity_general_deal(1);
	}
};


bool clear_all_door=0;
class DOOR:public Entity
{//传送门  成对的门是一个实体
public:
	int sx,sy,tx,ty,backgroundColor,color;
	string slook,tlook;
	void init(int sx,int sy,int tx,int ty,int color,int bkColor,string slook,string tlook){this->sx=sx;this->sy=sy;this->tx=tx;this->tx=tx;putUpdate();this->color=color;backgroundColor=bkColor;this->slook=slook;this->tlook=tlook;isExist=1;update();}
	void init(int sx,int sy,int tx,int ty){gto(1,0);cout<<randoom(9);this->sx=sx;this->sy=sy;this->tx=tx;this->tx=tx;isExist=1;speed=500;backgroundColor=randoom(16);color=randoom(16);slook="A";tlook="A";update();}
	void show(){gto(sx,sy);SetColor(color,backgroundColor);cout<<slook;gto(tx,ty);cout<<tlook;COLOR}
	void clear(){for(int i=sy;i<=sy+slook.size();i++){print_char(sx,sy);}for(int i=ty;i<=ty+tlook.size();i++){print_char(tx,i);}}
	void update(){
		putUpdate();
		gto(1,0);cout<<get_rand(1,9);
		if(clear_all_door){isExist=0;clear();return;}
		if(!speedCheck())return;
		show();
		EntityMap[sx][sy].nx=tx,EntityMap[sx][sy].ny=ty;
		EntityMap[tx][ty].nx=sx,EntityMap[tx][ty].ny=sy;
	}
};

class EldritchHorror:public Entity
{
public:
	void MengYan(){
		int tx=player->x,ty=player->y;
		
	} 
	void RemoveMengYan(){
		int tx=player->x,ty=player->y;
		
	} 
	void show(){
		
	}
	void update(){
		
	}
};


































































