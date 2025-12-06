#pragma once
#include<iostream>
#include<vector>
#include<string>

#define MAP_X_MAX maxX-1
#define MAP_Y_MAX maxX-15



struct MapBlock{
	_charInfo charInfo;
	int hard,dHealth;
	
	MapBlock(){}
	MapBlock(int _hard) : hard(_hard) {}
	MapBlock(int _hard,_charInfo NewCharInfo) : hard(_hard) , charInfo(NewCharInfo){}
	MapBlock(int _hard,int _dHealth) : hard(_hard) , dHealth(_dHealth) {}
	MapBlock(int _hard,int _dHealth,_charInfo NewCharInfo) : hard(_hard) , dHealth(_dHealth) , charInfo(NewCharInfo){}
	
	void clear(){hard=0;dHealth=0;charInfo.clear();}
	
};

vector<vector<MapBlock>> Map(256,vector<MapBlock>(256));



class GAMEMAP : public ObjectBase  
{
public:
	
	GAMEMAP();
	void init();
	void update();
	void MapSpawn(int type);
	void MapLoad(int num);
	int SpecificRandomForMapSpawn(int a);
	void create_Spawning(int x,int y,vector<vector<MapBlock>>& Spawning);
};

       

class WORLD : public ObjectBase
{
public:
	WORLD();
	GAMEMAP* GameMap=nullptr;
	void init();
	void update();
};


WORLD* World=nullptr;

