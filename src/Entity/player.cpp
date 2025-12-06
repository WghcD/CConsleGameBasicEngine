#include "Player.h"

Player::Player(){init();}

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
    putUpdate(); 
    if(!canUpdate()){/*Log(to_string(lastUpdate)+" "+to_string(clock()-lastUpdate)+" "+to_string(updateSpeed)); */return; }
	//Log("Player can update");

    playerConrol();
	render();
	("Player Posision: "+to_string(pos.x)+" "+to_string(pos.y));
}

void Player::render() {
    Buffer.write(uuid,pos.x,pos.y,'@',10);

}



void Player::init(){
	putUpdate();
	updateSpeed=70;
	pos.x=1,pos.y=1;
	Log("Player Init SSCC");
}

Player* player = nullptr;
