#include"Game/game.cpp"

int main () {
	Log("Hello World!");
	game=new Game;
	game->init();

	while(IsRunning){
		game->run();
	}
	game->end();
	return 0;
}

