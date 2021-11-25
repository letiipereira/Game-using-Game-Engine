#pragma once
#include "Enemy.h"
#include "Spawner.h"

class Loner : public Enemy
{
public:
	Loner(int posX, int posY, Spawner* spawner);
	~Loner() override final;

	void Update() override final;
	void Init() override final;

private:
	Spawner* mySpawner{ nullptr };
	Animation* idleLoner{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
	float moveSpeed = 100.0f;
	float uniform = 0.7071f;
};

