#pragma once
#include "Entity.h"

class Missile :  public Entity
{

public:
	Missile(int posX, int posY, float movementX, float movementY);
	~Missile() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

private:
	Animation* missileEnAnim{ nullptr };
	Animation* die{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
	float missileMovX{};
	float missileMovY{};
	float speed = 5.0f;
	bool hasCollided;
};

