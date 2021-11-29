#pragma once
#include "Entity.h"

class Bullet :  public Entity
{
public:
	Bullet(int posX, int posY);
	~Bullet() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

private:
	Animation* bulletAnim{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
};

