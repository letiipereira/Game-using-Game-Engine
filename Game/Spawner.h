#pragma once
#include "Entity.h"
#include <vector>
#include "Enemy.h"

class Spawner : public Entity
{
public:
	Spawner();
	~Spawner();

	void Update() override final;
	void Init() override final;

	void SpawnLoner();
	void SpawnRusher();

private:

	float lonerSpawnRate{5};
	float rusherSpawnRate{8};
	float lonerDeltaTime{0};
	float rusherDeltaTime{ 0 };

	std::vector<Enemy*> levelEnemies{};
};

