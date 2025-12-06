#pragma once

//消息表
#define DESTORY 5135
#define BREAK 48531
#define SLEEP 145315
#define START 153210
#define INIT 15315

class BaseClass{//消息机制
public:
	int state;
	virtual void getMessage(int Message){}
	virtual void dealMessage(int Message){}
};