#pragma once

#include<cstdio>
#include<dos.h>
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
#include <execution> // C++17引入的执行策略头文件
#include <numeric> // for std::iota
#include"public.h"
#include"../Game/log.cpp"

#include"Consle.cpp"
#define COLOR SetColor(7,16);
#define MAX HIGH*WIDE+100
#define CLS system("cls");
#define PAUSE system("pause>nul");

#define TITLE "Boom"
//#define HIGH 207                  

#define HIGH 147//主地图宽
#define WIDE 61//主地图高
#define RHIGH HIGH*2
#define RWIDE WIDE*2

#define CONHIGH 71 //窗口高
#define CONWIDE 253 //窗口宽

//#define WIDE 70
using namespace std;
template <typename T, typename... Args>
using FuncPtr = T (*)(Args...);


stack<int> active_entity_list;//存储当前主循环中的活跃实体
vector<vector<Entity_infor>> EntityMap(1000,vector<Entity_infor>(1000));


int xp_pl;

bool allow_bullet_update = true;
int x_pl = 7, y_pl = 7;
int last_randoom = -1;
int blood_pl = INT_MAX;

void clear(short x, short y);
void gto(int x, int y);
int get_bullet();
void SetColor(int ForgC, int BackC);
int randoom(int a);

template <typename T, size_t N>
void copyArray(const T (&src)[N], T (&dest)[N]) {
    std::copy(std::begin(src), std::end(src), std::begin(dest));
}
template <typename T, size_t ROWS, size_t COLS>
void copy2DArray(T (&src)[ROWS][COLS], T (&dest)[ROWS][COLS]) {
    memcpy(dest, src, ROWS * COLS * sizeof(T));
}


void Gto(int x, int y) {
	if(x<0||y<0){Gto(0,0);}
	COORD pos; pos.X = y*2; pos.Y = x*2;
	SetConsoleCursorPosition(conhandle, pos);
}

int randoom(int a) {
	srand(clock() + a * 177);
	
	srand(rand()%last_randoom);
	int n = rand() % a + 1;//1~a的伪随机数
	last_randoom = n * 17;
	return n;
}

char randoom_char(){
	int n=randoom(26);
	char a='A'+char(n);
	return a;
}



char get_randoom_der(){
	char tmp='a';
	if(randoom(4)==1)tmp='a';if(randoom(4)==2)tmp='s';if(randoom(4)==3)tmp='w';if(randoom(4)==4)tmp='d';
	return tmp;
}


void SetColor(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void Color(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}



bool fileExist(string name){
	return !(access(name.c_str(),F_OK));
}

/*void gto(int x, int y) {
	COORD pos; pos.X = y; pos.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}*/



void SendKeyStroke(DWORD key) {
    //keybd_event(key, 0, 0, 0);
    //keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

void noedit(){
	HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;
	mode&=~ENABLE_INSERT_MODE;
	mode&=~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin,mode);
}

void ConsleInit() {
	conhandle=GetStdHandle(STD_OUTPUT_HANDLE);
	noedit();

	
	string a="title ",b=TITLE;
    string commond=a+b;
    system(commond.c_str());

	
	
	
	
	SetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; 
	SetConsoleCursorInfo(hOut, &cursor_info);


	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);

	//set_classic();
	//thread INPUT(input_player_and_deal);
	//INPUT.detach();
    
	HWND hWnd=GetForegroundWindow();
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    
	HANDLE Hand;
	CONSOLE_SCREEN_BUFFER_INFO Info;
	Hand = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(Hand, &Info);
	SMALL_RECT rect = Info.srWindow;
	COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//定义缓冲区大小，保持缓冲区大小和屏幕大小一致即可取消边框 
	SetConsoleScreenBufferSize(Hand, size);
	
	
	//for (int i = 153; i < 180; i++) { gto(WIDE - line_sum_big-1, i); printf("="); }
	for(int i=0;i<=61;i++){gto(i,180);printf("|");}

	

	//if(noC){ios::sync_with_stdio(false);}


}
int get_rand(int a,int b){
	int n=randoom(a+b);
	return n%b;
}










