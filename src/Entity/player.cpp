#include "Player.h"

Player::Player(){setX(1),setY(1);init();}

Player::Player(int x,int y){setX(x);setY(y);init();}

void Player::playerConrol() {

	int lx=getX(),ly=getY();

    if(getKey('w')){ changeX(-1);/*Log("Player x+=1");*/}
    if(getKey('s')){changeX(1);/*Log("Player x-=1");*/}
    if(getKey('d')) {changeY(1);/*Log("Player y+=1");*/}
    if(getKey('a')) {changeY(-1);/*Log("Player y-=1");*/} 
    if(getKey('e')) {}
    if(getKey('l')) {}
    if(getKey('k')) {}
    if(getKey('x')) {}
	if(getX()<0||getY()<0||getX()>=maxX||getY()>=maxY){setX(lx),setY(ly);}
	
	
	
	
	
}

void Player::update() {


    playerConrol();
	render();
	("Player Posision: "+to_string(pos.x)+" "+to_string(pos.y));
}

void Player::render() {
	//Log("Player Render Start");
    Buffer.write(uuid,pos.x,pos.y,'@',10);
	//Log("Player Render End");
}



void Player::init(){
	
	updateSpeed=70;
	
	Log("Player Init SSCC");
}

Player* player = nullptr;
