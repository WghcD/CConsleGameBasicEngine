#pragma once
#include"../Include/head.h"
#include"../Include/graphics.h"
#define G 0.15//重力大小

int Tan(double angle){
	double radians = angle * (M_PI / 180.0);
	return tan(radians);
}

struct ControlMap{
	bool isActive;//位置是否被激活
	int ActiveLevel=0;
	void changeActiveLevel(int ActiveLevel){this->ActiveLevel=ActiveLevel;if(ActiveLevel!=0){isActive=1;}else{isActive=0;}}
	bool getActive(){return isActive;}
};
ControlMap control_map[1001][1001];
class activeEntity{
	ControlMap activeCondition;//自己的状态
	virtual active(){}
	virtual unactive(){}
};


class Force{
	public:
	double xF,yF;//数学上两个有符号实数表示一个平面向量
	void init(double xF,double yF){this->xF=xF,this->yF=yF;}
	void init(int angle,int F,int n){//angle角度  F动量必须为正!  n象限
		if(n==1)xF=F;yF=Tan(angle)*F;
		if(n==2)xF=F*-1.0;yF=Tan(angle)*F;
		if(n==3)xF=F*-1.0;yF=Tan(angle)*F*-1.0;
		if(n==4)xF=F;yF=Tan(angle)*F*-1.0;
	}
};
#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0:1)//按键释放
#define Key_Down(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)//按键按下
char input() {
	if (Key_Down(' ') || Key_Down(' '))
		return ' ';
	for(char now='a';now<='z';now++){
		if(Key_Down(now)||Key_Down(toupper(now)))
			return now;
	}
	return 'N';
}