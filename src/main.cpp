#include"Game/game.cpp"

int main () {
	Log("Hello World!");
	game=new Game;
	game->init();

	Circle1* obj = AM<Circle1>();

	while(IsRunning){
		game->run();
		Sleep(12);
	}
	game->end();
	return ExitCode;
}

