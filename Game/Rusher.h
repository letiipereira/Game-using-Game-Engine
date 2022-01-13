#pragma once
#include "Enemy.h"
#include "Spawner.h"

class Rusher :  public Enemy
{
public:
	Rusher(int posX, int posY, Spawner* spawner);
	~Rusher() override final;

	void Update() override final;
	void Init() override final;	

private:
	Spawner* mySpawner{ nullptr };
	Animation* idleRusher{ nullptr };
	int spawnPosX{};
	int spawnPosY{};
	float moveSpeed{ 100.0f };
	float uniform{ 0.7071f };
};

