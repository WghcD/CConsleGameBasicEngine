#include"main.h"



int main () {
	game=AM<GAME>();
	game.init();
	while(isRunning){
		game.run();
	}
	
	return 0;
}