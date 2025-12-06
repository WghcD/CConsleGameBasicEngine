#pragma once
#include"../Include/object_base.h"
#include <functional>
#include <queue>







class EntityBase : public ObjectBase                    
{
public:
    Point pos;
    bool isLiving;
    bool isActive;

	int lastUpdate=0,updateSpeed=130;
    EntityBase(void);
    int getX();
    int getY();
	void changeX(int dx);
	void changeY(int dy);
	void setX(int _x);
	void setY(int _y);
    void changePos(Point newPos);
    void changePos(int x, int y);
    virtual void update();
    virtual void render();
    virtual void SelfKill();
    virtual void create();
	virtual void init();


	bool canUpdate();
    void putUpdate();
};




class DamageBase {
protected:
    bool isDA;
    bool isArmor;
    bool isResilience;
    bool canKill;
    bool isKill;
    bool fromPlayer;
    bool fromEnemy;
public:
    DamageBase(void);
};

class LivingEntityBase : public EntityBase {
protected:
    int HP;
public:
    LivingEntityBase(void);
    void update() override;
    void create() override;
    void render() override;
    void SelfKill() override;
};

class AttackEntityBase : public EntityBase {
protected:
    int AimNumber;
public:
    AttackEntityBase(void);
    void update() override;
    void create() override;
    void render() override;
    void SelfKill() override;
};
