#include"game.h"







Game::Game(){get_uuid(SYSTEM_TYPE);}

void Game::init(){

	ConsleInit();
	
	World=new WORLD();

	player=new Player();
	
	KeyInput.Start();
	
	Log("Init OK");

}

void Game::DebugPrint(){
	static int uuidForDebugPrint=outside_get_uuid(0);//Game类的不同输出模块使用独立uuid
	int s=0;
	buffer.write(uuidForDebugPrint,s++,InfoPrintStartY,"Object Cnt=>"+to_string(DebugInfo.ObjectCntNow));
	buffer.write(uuidForDebugPrint,s++,InfoPrintStartY,"LastMainLoopTimeCost=>"+to_string(MAIN));
	Point pos1=getMousePos();buffer.write(uuidForDebugPrint,s++,InfoPrintStartY,"MousePos x=>"+to_string(pos1.x)+" y=>"+to_string(pos1.y)+"  LeftClick"+to_string(LeftClick()));
}

void Game::GeneralGameUpdate(){//与游戏本体相关的所有工作
	static int GGUuuid1=outside_get_uuid(0);
	if(DEBUG_MODE){
	DebugPrint();
	MAIN=clock()-lastMain;
	lastMain=clock();
	}
	
	
	
}

void Game::run(){

	GeneralGameUpdate();
	
	
	
	
	

	Buffer.update();
	
	DebugInfo.ObjectCntNow=ObjectUpdate();
	
	World->update();
	
}

void Game::broke(int seconds){
	Sleep(seconds*1000);
}

void Game::end(){
	CLS
	gto(0,0);cout<<"Programm will exit with ExitCode "<<ExitCode;
	if(ExitCode!=0){gto(1,0);cout<<"Programm exited because of an occured error . Please check the Log file";
	gto(2,0);if(ExitText!="N"){cout<<"ErrorInfo: "<<ExitText;}else cout<<"No text is prepared for explaining this error.ExitText is empty.";
	}
	gto(3,0);cout<<"Press Any Key To Exit";
	PAUSE
	Log("Program Exit Properly.");
}

