#pragma once
#include"InteractiveControls.h"
#include"graphics.h"


queue<std::function<void()>> InteractiveControlUpdateQueue;
class InteractiveControl
{
	public:
	bool isExist;
	int x,y,state,color;
	Func work;
	virtual void show(){}
	virtual void clear(){}
	virtual void update(){}
	virtual void init(){}
	void putUpdate(){if(!isExist){return;}InteractiveControlUpdateQueue.push(std::bind(&InteractiveControl::update, this));}
};

class Button:public InteractiveControl
{
	public:
	string info;
	bool selfDestory=0;
	int lastShow,lenth;
	void clear(){for(int i=0;i<=lenth;i++){GameMap->block[x/2][i/2].Bprint(x/2,i/2);}}
	void init(int x,int y,string info,Func work){this->x=x,this->y=y,this->info=info,this->work=work;lenth=info.size();}
	void update(){
		putUpdate();
		if(clock()-lastShow>401){lastShow=clock();gto(x,y);cout<<info;}
		if(cursor_x()==x&&cursor_y()>=y&&cursor_y()<=y+lenth+1){
			clear();gto(x,y);Color(color,8);cout<<info;COLOR
			if(key_down()){work();if(selfDestory){clear();isExist=0;}}
		}
	}
};
class IC1:public Button//专门用于开始界面
{
	public:
	int sizeX,sizeY;
	string info;
	void init(int x,int y,int sizeX,int sizeY,string info,Func work){this->x=x,this->y=y,this->sizeX=sizeX,this->sizeY=sizeY,this->info=info,this->work=work;isExist=1;}
	void update(){
		if(!isExist)return;
		putUpdate();
		if(clock()-lastShow>401){color=randoom(16);line(x,y+1,x,y+sizeY-1,color,'=');line(x+1,y+sizeY,x+sizeX-1,y,color,'#');line(x+sizeX,y+1,x,y+sizeY-1,color,'=');line(x+1,y,x+sizeX-1,y,color,'#');
		SetColor(4,16);gto(x,y);printf("+");gto(x+sizeX,y);printf("+");gto(x+sizeX,y+sizeY);printf("+");gto(x,y+sizeY);printf("+");SetColor(11,16);gto(x+(x+sizeX)/2,y+(y+sizeY)/2-lenth/2);cout<<info;COLOR }//绘制边框 显示文字
		if(cursor_x()>=x&&cursor_x()<=x+sizeX&&cursor_y()>=y&&cursor_y()<=y+sizeY){
			clear();gto(x,y);Color(color,8);cout<<info;COLOR
			if(key_down()){
				if(state==1){
				work();isExist=0;
				if(state==0){state=1;}
			}
		}
	}
}
}; 
void IC_update(){
	while(!InteractiveControlUpdateQueue.empty()){
		InteractiveControlUpdateQueue.front()();//执行update()
		InteractiveControlUpdateQueue.pop();
	}
}