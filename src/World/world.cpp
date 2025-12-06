#include"world.h"


int GAMEMAP::SpecificRandomForMapSpawn(int a){
	static int last_randoom = -114514;
	srand(clock() + a * 177);
	for (int i = 1; i <= 3; i++)
		srand(rand() / 13 + clock() - a % 6 + last_randoom / 7 * 2 + 1);
	srand(last_randoom*rand());
	int n = rand() % a + 1;//1~a的伪随机数
	last_randoom = n * 17;
	return n;
}


void GAMEMAP::init(){Log("GameMap Class Init Comletely");}
	
GAMEMAP::GAMEMAP() {
	get_uuid(MAP_TYPE);
	Buffer.write(uuid,10,10,"TEST",114514);
	Log("GameMap Class Build Comletely");
	
	init();
}

void GAMEMAP::update(){
	
}

void GAMEMAP::create_Spawning(int x,int y,vector<vector<MapBlock>>& Spawning){
	/*
	for(int i=x;i<MAP_X_MAX;i++){//初步生成
		
		if(SpecificRandomForMapSpawn(5)==SpecificRandomForMapSpawn(6)){//平均五行一段墙壁
		for(int k=0;k<=2;k++){
	        int tmp1=SpecificRandomForMapSpawn(MAP_Y_MAX-6);
			for(int j=y;j<tmp1+SpecificRandomForMapSpawn(5)+5;j++){
				Spawning[i][j].look='#';Spawning[i][j].hard=1;
			}
		}
		}
	}
	*/
}

void GAMEMAP::MapSpawn(int type){
	/*
	vector<vector<MapBlock>> Spawning(256,vector<_charInfo>(256));





	for(int i=0;i<MAP_X_MAX;i++){//初始化
	for(int j=0;j<MAP_Y_MAX;j++){
		Spawning[i][j].clear();
	}
	}
	
	
	for(int i=0;i<MAP_X_MAX;i++){//初步生成
		
		if(SpecificRandomForMapSpawn(5)==SpecificRandomForMapSpawn(6)){//平均五行一段墙壁
		for(int k=0;k<=2;k++){
	        int tmp1=SpecificRandomForMapSpawn(MAP_Y_MAX-6);
			for(int j=tmp1;j<tmp1+SpecificRandomForMapSpawn(5)+5;j++){
				Spawning[i][j].look='#';Spawning[i][j].hard=1;
			}
		}
		}
	}
	
	for(int i=0;i<MAP_X_MAX;i++){//开墙
		for(int j=0;j<MAP_Y_MAX;j++){
			if(!Spawning[i][j].hard){
				create_Spawning(i,j,Spawning);
			}
		}
	}
	int sum=0;
	int n=0;
	for(int i=0;i<MAP_X_MAX;i++){
		for(int j=0;j<MAP_Y_MAX;j++){
			if(SpecificRandomForMapSpawn(100)==17)n=0;
			if(Spawning[i][j].hard)sum++;
			if(sum>10){
				sum=0;
				for(int k=j;k<j+SpecificRandomForMapSpawn(7)+n;k++){
					Spawning[i][k].look='N',Spawning[i][k].hard=0;
				}
				n++;
			}
		}
	}
	for(int i=0;i<MAP_Y_MAX;i++)//防止玩家一出生就卡墙里
	{Spawning[x_pl][i].hard=0;Spawning[x_pl][i].look='N';}
	
	
	
	for(int i=1;i<10;i++){//画岩浆与水
		int t1=SpecificRandomForMapSpawn(MAP_X_MAX-1),t2=SpecificRandomForMapSpawn(MAP_Y_MAX-1);
		int color=4;
		if(SpecificRandomForMapSpawn(132)%2==1)color=3;
		Spawning[t1][t2].look='M';Spawning[t1][t2].color=color;Spawning[t1][t2].isflow=1;if(color==4)Spawning[t1][t2].hit=15;
	}
	

	for (int j=2;j<MAP_Y_MAX;j++) //边界处理 
	{
		Spawning[0][j-1].look='#';
		Spawning[0][j-2].look='#';
		Spawning[MAP_X_MAX-1][j].look='#';
		Spawning[0][j-1].hard=2;
		Spawning[MAP_X_MAX-1][j].hard=2;
		Spawning[0][j-2].hard=2;
	}
	
	for(int i=0;i<=SpecificRandomForMapSpawn(3)+pass*2;i++){//画陷阱
	int t1=SpecificRandomForMapSpawn(MAP_X_MAX-1),t2=SpecificRandomForMapSpawn(MAP_Y_MAX-1);
	if(Spawning[t1][t2].hard==0&&!Spawning[t1][t2].isflow){
		
		Spawning[t1][t2].look='F';
		Spawning[t1][t2].hard=1;
		Spawning[t1][t2].bullet_look='X';
		Spawning[t1][t2].bullet_hit=SpecificRandomForMapSpawn(5)+pass*2;
		Spawning[t1][t2].color=SpecificRandomForMapSpawn(14)+1;
		Spawning[t1][t2].der=get_SpecificRandomForMapSpawn_der();
		Spawning[t1][t2].type=1;
	}
	}
	
	int t1=SpecificRandomForMapSpawn(MAP_X_MAX-2),t2=SpecificRandomForMapSpawn(MAP_Y_MAX-2);
	Spawning[t1][t2].look='$';Spawning[t1][t2].hard=2;Spawning[t1][t2].color=2;//生成出口
	sum=0;
	for(int i=t1-5;i<=t1+5;i++){
		if(sum>10)break;
		for(int j=t2-5;j<=t2+5;j++){
			
			int tmp=10;
			if(tmp-pass>3)tmp-=pass;else tmp=3;
			if(SpecificRandomForMapSpawn(tmp)==1&&Spawning[i][j].look=='N'){
				sum++;
				Spawning[i][j].look='F';
				Spawning[i][j].hard=1;
				Spawning[i][j].bullet_look='X';
				Spawning[i][j].bullet_hit=SpecificRandomForMapSpawn(5)+pass*2;
				Spawning[i][j].color=SpecificRandomForMapSpawn(14)+1;
				Spawning[i][j].der=get_SpecificRandomForMapSpawn_der();
				Spawning[i][j].type=1;
			}
		}
	}
	
	
	Spawning_first=1;
	
	for(int i=1;i<10;i++){
		t1=SpecificRandomForMapSpawn(MAP_X_MAX-1),t2=SpecificRandomForMapSpawn(MAP_Y_MAX-1);
		if(SpecificRandomForMapSpawn(i)==SpecificRandomForMapSpawn(10)){
			Spawning[t1][t2].type=13;
		}
		if(SpecificRandomForMapSpawn(i)==SpecificRandomForMapSpawn(15)){
			Spawning[t1][t2].type=12;
		}
	}
	
	
	
	
	
	
	
	last_create_win=clock();
	*/

}

void GAMEMAP::MapLoad(int num){
	
}

void WORLD::update(){
	GameMap->update();
}

void WORLD::init(){
	Log("World Class Init Completely");
}

WORLD::WORLD(){
	get_uuid(SYSTEM_TYPE);
	GameMap=new GAMEMAP();
	Log("World Class Build Comletely");
	init();
}


















































