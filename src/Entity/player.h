#pragma once
#include "entity.h"
#include "../Consle/Input.h"

class Player : public LivingEntityBase 
{
private:
    void playerConrol();
    
public:
	Player();
    void update() override;
    void render() override;
	void init() override;
};

extern Player* player;