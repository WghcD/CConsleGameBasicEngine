#pragma once

#define TYPE short

#define SYSTEM_TYPE 0 
#define MAP_TYPE 1
#define ENTITY_TYPE 2
#define EFFECT_TYPE 3

#define CONTINE 1

#define UUID_MAX 114514



vector<bool> uuidUsedList(UUID_MAX+1,false);
const int ObjectTypeBound[]={0,UUID_MAX/4,UUID_MAX/2,UUID_MAX/4*3,UUID_MAX};

TYPE IdToType(int id){
	for(TYPE i=0;i<=3;i++){
		if(id>=ObjectTypeBound[i]&&id<ObjectTypeBound[i+1]){return i; }
	}
	Log("Fuck:Bad IdToType Request");
	return SYSTEM_TYPE;
}



class ObjectBase{//一切对象的基类
public:
	int uuid=-1;//通用唯一标识符

	void get_uuid(int Type){
		int i;
		for(i=ObjectTypeBound[Type];i<ObjectTypeBound[Type+1];i++){
			if(!uuidUsedList[i]){uuidUsedList[i]=true;break;}
		}
		if(i<UUID_MAX)uuid=i;
		else{Log("\n\n[!]Get uuid for object failed. Reason:the uuid was too large to UUID_MAX! \n\n");IsRunning=0;ExitCode=1;}
		//Log("Getted uuid "+to_string(uuid));
	}
	void destory_uuid(){
		uuidUsedList[uuid]=false;//Free the uuid used.
	}
	~ObjectBase () {
		destory_uuid();
	}
};


std::queue<std::function<void()>> ObjectUpdateQueue;  
std::queue<std::function<void()>> BackObjectUpdateQueue;  
int ObjectUpdate(){
	int cnt=0;
	while(!ObjectUpdateQueue.empty()){
		ObjectUpdateQueue.front()();cnt++;
		ObjectUpdateQueue.pop();
	}
	while(!BackObjectUpdateQueue.empty()){
		ObjectUpdateQueue.push(BackObjectUpdateQueue.front());
		BackObjectUpdateQueue.pop();
	}
	return cnt;
}
