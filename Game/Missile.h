#pragma once
#include "Entity.h"

class Missile :  public Entity
{

public:
	Missile(int posX, int posY);
	~Missile() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

private:
	Animation* missileEnAnim{ nullptr };
	Animation* die{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
	bool hasCollided;
};

