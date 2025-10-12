#pragma once
#include"../Include/head.h"
#include"../Map/map.cpp"
#include"../Include/InteractiveControls.cpp"
#include"../Entity/entity.cpp"






class GAME{
public:
	void init(){
		Buffer=AM<DoubleBuffer>(CONWIDE,CONHIGH);
		Buffer->init();
		
		ConsleInit();
		isRunning=1;
		
		player=AM<PLAYER>();
	    player->init();
		WL("Player Init Successfully");
		

		test();
		WL("Test Finished");
	}
	void end(){
		WL("Game Exit Normolly");
		exit(0);
	}
	void broke(){
		WL("Main Thread Has Been Broken Normolly");
		while(1){Sleep(500);}
	} 
	void run(){
		buffer = Buffer->getBuffer();
		entity_update();
		IC_update();
		run_speed_compute();
		
		Buffer.flash();
		
	}
	void run_speed_compute(){
	gto(22,182);printf("        ");gto(32,152);
	printf("MAIN=>");
	cout<<clock()-last_main<<" ms";
	MAIN=clock()-last_main;
	last_main=clock();
	}
	void test(){
    return;	
	}
};

GAME* game=nullptr;

