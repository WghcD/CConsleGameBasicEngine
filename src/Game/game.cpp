#include"game.h"


void Game::init(){


	ConsleInit();
	
	
	World=new WORLD();

	
	
	player=new Player();
	
	
	KeyInput.Start();
	Log("Init OK");

}

void Game::run(){
	
	//if(!signalQueue.empty()){/*消息处理....*/}
	Buffer.update();
	entityUpdate();
	World->update();

}

void Game::broke(int seconds){
	Sleep(seconds*1000);
}

void Game::end(){
	CLS
	gto(0,0);cout<<"Programm will exit with ExitCode"<<ExitCode;
	if(ExitCode!=0){gto(1,0);cout<<"Programm exited because of an occured error . Please check the Log file";
	gto(2,0);if(ExitText!="N"){cout<<"ErrorInfo: "<<ExitText;}else cout<<"No text is prepared for explaining this error.ExitText is empty.";
	}
	gto(3,0);cout<<"Press Any Key To Exit";
	PAUSE
}

