#include"Game/game.cpp"


void StressTest(){
	int Count=10000;
	while(Count--){
		Player* obj = AM<Player>(Rand(maxX),Rand(maxY));//不用留指针
		FireworkSample* obj2 = AM<FireworkSample>();
		ClockSample* obj3=AM<ClockSample>();
	}
}

int main () {
	
	
	
	Log("Hello World!");
	game=new Game;
	game->init();
	
	
	//StressTest();
	FireworkSample* obj2 = AM<FireworkSample>();
	ClockSample* obj3=AM<ClockSample>();
	
	
	obj2->destroy();

	Log("!!!");
	while(IsRunning){
		game->run();
	}
	game->end();
	return ExitCode;
}

