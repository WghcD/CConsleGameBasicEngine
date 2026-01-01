#pragma once
#include"entity.h"

                   
EntityBase::EntityBase(void) : isLiving(1),isActive(1){get_uuid(ENTITY_TYPE);Log(to_string(uuid));}//So That Entity不需要显式调用get_uuid
int EntityBase::getX(){return pos.x;}
int EntityBase::getY(){return pos.y;}
void EntityBase::changePos(Point newPos){pos=newPos;}
void EntityBase::changePos(int x,int y){pos.x=x,pos.y=y;}
void EntityBase::changeX(int dx){pos.x+=dx;}
void EntityBase::changeY(int dy){pos.y+=dy;}
void EntityBase::setX(int _x){pos.x=_x;}
void EntityBase::setY(int _y){pos.y=_y;}
void EntityBase::update(){}
void EntityBase::render(){}
void EntityBase::SelfKill(){isLiving=false;destory_uuid();Log("Entity "+to_string(uuid)+" has been Destoried");}

void EntityBase::create(){}


void EntityBase::putUpdate(){BackObjectUpdateQueue.push(std::bind(&EntityBase::update, this));}
bool EntityBase::canUpdate(){if(clock()-lastUpdate>updateSpeed){lastUpdate=clock();return true;}else{return false;}}

void EntityBase::init(){}




DamageBase::DamageBase(void) : isDA(1),isArmor(1),isResilience(1),canKill(1),isKill(0),fromPlayer(0),fromEnemy(0){}


LivingEntityBase::LivingEntityBase(void) : HP(0){}
void LivingEntityBase::update(){}
void LivingEntityBase::create(){}
void LivingEntityBase::render(){}
void LivingEntityBase::SelfKill(){}

AttackEntityBase::AttackEntityBase(void) : AimNumber(0) {}
void AttackEntityBase::update(){}
void AttackEntityBase::create(){}
void AttackEntityBase::render(){}
void AttackEntityBase::SelfKill(){}



