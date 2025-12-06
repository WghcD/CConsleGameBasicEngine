#pragma once



#include"../Include/include.h" //包含基础类与基础函数

//所有二级类的源都放在这里  就不用添在编译指令里了

#include"../Entity/entity.cpp"
#include"../Entity/player.cpp"
#include"../World/world.cpp"
	


class Game{
public:
	void init();
	void run();
	void broke(int seconds);
	void end();
};
Game* game=NULL;