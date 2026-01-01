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
	 buffer.write(uuid,1,InfoPrintStartY,"Object Cnt=>"+to_string(DebugInfo.ObjectCntNow));
}

void Game::run(){

	
	if(DEBUG_MODE)DebugPrint();

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

