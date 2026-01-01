#include <ctime>
#include <cstdio>
#include <windows.h>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>
using namespace std;
HANDLE _conhandle=NULL;




#define buffer Buffer



void MoveConsoleToTopLeft() {
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    
    // 计算窗口当前位置与目标位置的偏移量
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    // 移动到屏幕左上角(0,0)且保持原尺寸
    MoveWindow(console, 0, 0, width, height, TRUE);
}
void DisableConsoleResize() {
    HWND console = GetConsoleWindow();
    
    // 获取当前窗口样式
    LONG style = GetWindowLong(console, GWL_STYLE);
    
    // 移除可调整大小、最大化的样式
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
    SetWindowLong(console, GWL_STYLE, style);
    
    // 禁用F11全屏快捷键
    HMENU hMenu = GetSystemMenu(console, FALSE);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
}

void _SetColor(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F); 
	SetConsoleTextAttribute(_conhandle, wColor);
}

void _gto(int x, int y) {
	if(x<0||y<0){_gto(0,0);}
	COORD pos; pos.X = y; pos.Y = x;        
	SetConsoleCursorPosition(_conhandle, pos);
}

void _HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;       // 光标大小（1-100百分比）
    cursorInfo.bVisible = FALSE; // 可见性设为FALSE
    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &cursorInfo  
    );
}

class _charInfo{
public:
	_charInfo(){;}
	_charInfo(char sw,int fc,int bc) : isUsed(true) , show(sw) , ForgC(fc) , BackC(bc) {;}
	_charInfo(int fc,int bc,char sw) : isUsed(true) , show(sw) , ForgC(fc) , BackC(bc) {;}
	bool isUsed=false;
	int ForgC=10,BackC=16;
	char show=' ';
	void set(char show,int ForgC, int BackC){this->show=show;this->ForgC=ForgC;this->BackC=BackC;isUsed=1;}
	bool operator==(const _charInfo a) const {
		return a.ForgC==ForgC&&a.BackC==BackC&&a.show==show;
	}
	/*&_charInfo operator=(const _charInfo& other){
		if(this==&other){Log("Fuck from charInfo operator=");}
		return *this;
	}*/
	void clear(){show=' ',ForgC=10,BackC=16;isUsed=0;}
};

class BufferBase
{
protected:



_charInfo buffer[2][266][266];
_charInfo layers[5][266][266];

struct ClearTask{
	int layerN;
	int x,y;
	int UT;

	char show;
	int ForgC,BackC;
	
	ClearTask (int _layerN,int _x,int _y,int _UT,int _ForgC,int _BackC,char _show) : x(_x), y(_y) ,  layerN(_layerN) , ForgC(_ForgC) , BackC(_BackC) , show(_show){this->UT=_UT;}

};





int MergeLayerPoint(int x,int y){//合并多图层上某一点至buffer
	for(int i=3;i>=0;--i){
		if(layers[i][x][y].isUsed){buffer[Now][x][y]=layers[i][x][y];return i;}
	}
	buffer[Now][x][y].clear();

	return -1;
}

int _TypeToLayer[4]={3,0,1,2};

int TypeToLayer(int n){if(n>=4){Log("Fuck:Bad request   From: Func TypeToLayer");}return _TypeToLayer[n];}

/*
多图层思路：
每次write尝试先写入layer一点  随后update buffer这一点  从高图层到低图层执行遍历  update后以最高优先级存在的有效字符作为buffer改点内容  在下一个Run周期内该uuid对象再次更新  则在清理残影等价于擦除先前layer的写入  再对buffer去update

即 layer是备用  包含被前面图层遮盖的点
buffer是front 前台渲染

图层优先级别值越高  越在前
*/
public:

	int FlipSpeed;
	int UT;//Update Times
	

	int Now=0,Last=1;
	BufferBase(int X, int Y,int s) : FlipSpeed(s) {
		_HideCursor();
		system(string("mode con cols="+to_string(Y)+" lines="+to_string(X)).c_str());
		MoveConsoleToTopLeft();
		DisableConsoleResize();

		if(_conhandle==NULL)_conhandle=GetStdHandle(STD_OUTPUT_HANDLE);
    }
	bool write(int x,int y,char show,int ForgC, int BackC){//最终被调用
		if(x<0||y<0||x>=maxX||y>=maxY)return false;
		buffer[Now][x][y].set(show,ForgC,BackC);
		return true;
	}
	bool write(int x,int y,string show,int ForgC,int BackC){
		for(int i=0;i<show.size();i++){
			if(write(x,y+i,show[i],ForgC,BackC))continue;
			else return false;
		}
		return true;
	}
	bool write(int x,int y,char show,int ForgC){
		return write(x,y,show,ForgC, 16);
	}
	bool write(int x,int y,string show,int ForgC){
		return write(x,y,show,ForgC,16);
	}
	
	void flip(){//BufferBase不提供面向对象的清理工作  也没有每帧清理所有内容的暴力清理
		for(int x=0;x<=maxX;x++){
			for(int y=0;y<=maxY;y++){
				if((!(buffer[Now][x][y]==buffer[Last][x][y]))){
				_gto(x,y);
				_SetColor(buffer[Now][x][y].ForgC,buffer[Now][x][y].BackC);
				printf("%c",buffer[Now][x][y].show);
				buffer[Last][x][y]=buffer[Now][x][y];
				}

			}
			
		}
		_SetColor(7,16);
	}
	bool update(){
		static int lastFlip=0;
		if(clock()-lastFlip>=FlipSpeed){
			if(UT<INT_MAX) UT++; else UT=0;
			flip();
			lastFlip=clock();
			return true;    
		}
		return false;
	}
	void SetTitle(const std::string& title) {
        SetConsoleTitleA(title.c_str());
    }
	
	/*以下为面向对象支持  uuid是调用方对象唯一编号  可以提供缓冲区自动清理上一次渲染   只有该组接口支持图层  因为图层取决于uuid*/
	
	unordered_map<int,stack<ClearTask>> RenderHistory;
	
	
	
	bool write(int uuid,int x,int y,char show,int ForgC, int BackC){//提供To Object支持的最终被调用   
		if(x<0||y<0||x>=maxX||y>=maxY)return false;
		
		int layerN=TypeToLayer(IdToType(uuid));//目标图层
		
		
		
		
		/*清理上次渲染痕迹*/
		while(!RenderHistory[uuid].empty()){
			if(RenderHistory[uuid].top().UT==UT){break;}/*防止把前面刚写入buffer[][]还没显示过的东西给清理掉了    也就是说这里默认一个对象一次渲染在一个帧间完成   这是可以的  因为一次主循环内一个对象的一次渲染必定完全完成  而多个主循环才会有一次帧渲染*/
			int _x=RenderHistory[uuid].top().x,_y=RenderHistory[uuid].top().y;
			//Log(to_string(_x)+" "+to_string(_y));
			layers[layerN][_x][_y].clear();//擦除指定图层上指定点内容
			int debugData=MergeLayerPoint(_x,_y);//更新buffer该点显示
			//Log(to_string(debugData));
			RenderHistory[uuid].pop();
		}
		/*清理完毕*/
		
		
		//Log(to_string(IdToType(uuid)));
		//Log(to_string(TypeToLayer(IdToType(uuid))));
		
		layers[layerN][x][y].set(show,ForgC,BackC);//写入指定图层上指定点指定内容
		MergeLayerPoint(x,y);//更新buffer该点显示
		
		ClearTask NewTask(layerN,x,y,UT,ForgC,BackC,show);
		RenderHistory[uuid].push(NewTask);
		
		return true;
	}
	bool write(int uuid,_charInfo ch,int x,int y){
		return write(uuid,x,y,ch.show,ch.ForgC,ch.BackC);
	}
	bool write(int uuid,int x,int y,_charInfo ch){
		return write(uuid,x,y,ch.show,ch.ForgC,ch.BackC);
	}
	bool write(int uuid,int x,int y,string show,int ForgC,int BackC){
		for(int i=0;i<show.size();i++){
			if(write(uuid,x,y+i,show[i],ForgC,BackC))continue;
			else return false;
		}
		return true;
	}
	bool write(int uuid,int x,int y,char show,int ForgC){
		return write(uuid,x,y,show,ForgC, 16);
	}
	bool write(int uuid,int x,int y,string show,int ForgC){
		return write(uuid,x,y,show,ForgC,16 );
	}
	bool write(int uuid,int x,int y,string show){
		return write(uuid,x,y,show,7,16 );
	}
	bool write(int uuid,string show,int x,int y){
		return write(uuid,x,y,show,7,16 );
	}
	bool write(int uuid,int x,int y){
		return write(uuid,x,y,' ',16,15);
	}
};





BufferBase Buffer(maxX,maxY,0);//第三个参数是每帧的间隔而不是每秒帧数，单位为ms












