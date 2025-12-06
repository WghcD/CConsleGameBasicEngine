#pragma once

#include<cstdio>
#include<cmath>
#include<windows.h>
#include<cstdlib>
#include<stdlib.h>
#include<string>
#include<sstream>
#include<algorithm>
#include<thread>
#include<fstream>
#include <unistd.h>
#include <dos.h>
#include<cstdio>
#include<stack>
#include<iostream>
#include<cmath>
#include<ctime>
#include<queue>
#include <vector>
#include <cctype>
#include<vector>
#include <functional>
#include <future>
#include <chrono>
#include <execution> 
#include <numeric> 
using namespace std;

using Func = std::function<void()>;

//#include"rand.h"
#include"Memory.h"
#include"base_class.cpp"
#include"base_func.cpp"



#define COLOR SetColor(7,16);
#define MAX HIGH*WIDE+100
#define CLS system("cls");
#define PAUSE system("pause>nul");

#define TITLE "NewStarting"
           

#define HIGH 147//主地图宽
#define WIDE 61//主地图高


#define CONHIGH 256 //窗口高
#define CONWIDE 256 //窗口宽

queue<int> signalQueue;

HANDLE conhandle=NULL;
int ExitCode;
string ExitText="N";
bool IsRunning=true;

struct Point{
	int x,y;
	Point(){}
	Point(int a, int b) : x(a), y(b) {}
	Point& operator=(const Point& other) {return *this;}
};

void SetColor(int ForgC, int BackC) {
	if(conhandle==NULL){conhandle=GetStdHandle(STD_OUTPUT_HANDLE);}
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(conhandle, wColor);
}

bool gto(int x, int y) {
	if(conhandle==NULL){conhandle=GetStdHandle(STD_OUTPUT_HANDLE);}
	if(x<0||y<0){gto(0,0);return false;}
	COORD pos; pos.X = y; pos.Y = x;
	SetConsoleCursorPosition(conhandle, pos);
	return true;
}


#define Rand get_rand
int last_rand;
int get_rand(int a){
	srand(141^clock()^last_rand);
	last_rand=rand()%a+1;
	return last_rand;
}

int get_rand(int a,int b){
	return a+get_rand(b-a);
}


#include"../Consle/log.h"
#include"object_base.h"
#include"../Consle/MyBuffer.h"
#include"../Consle/Input.h"
#include"../Consle/consle_util.h"
#include"../World/world.h"









