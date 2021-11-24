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

	void SpawnLoner(int spawnPosX, int spawnPosY);
	void SpawnRusher(int spawnPosX, int spawnPosY);
	void RemoveEnemy(Enemy* enemy);

private:

	float lonerSpawnRate{4};
	float rusherSpawnRate{3};
	float lonerDeltaTime{0};
	float rusherDeltaTime{0};
	int windowWidth{};
	int windowHeight{};

	std::vector<Enemy*> levelEnemies{};
};

