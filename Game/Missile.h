#pragma once
#include "Entity.h"

class Missile :  public Entity
{

public:
	Missile(int posX, int posY);
	~Missile() override;

	void Update() override;
	void Init() override;
private:
	Animation* missileEnAnim{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
	
};

