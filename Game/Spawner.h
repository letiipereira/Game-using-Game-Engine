#pragma once
#include "Entity.h"
#include "Spaceship.h"
#include <vector>
#include "Enemy.h"
#include "PowerUp.h"

class Spawner : public Entity
{
public:
	Spawner();
	~Spawner();

	void Update() override final;
	void Init() override final;

	void SpawnLoner(int spawnPosX, int spawnPosY);
	void SpawnRusher(int spawnPosX, int spawnPosY);
	void SpawnWeaponPU(int spawnPosX, int spawnPosY);
	void SpawnShieldPU(int spawnPosX, int spawnPosY);
	void SpawnCompanion(int spawnPosX, int spawnPosY);
	void CompanionNecessity(bool needCompanion);
	void RemoveEnemy(Enemy* enemy);
	void RemovePowerUp(PowerUp* powerUp);

	void SetPlayerReference(Spaceship* player);
	Vector2D GetPlayerPosition();

private:

	float lonerSpawnRate{4};
	float rusherSpawnRate{3};

	/*float weaponPUSpawnRate{20};
	float shieldPUSpawnRate{20};
	float companionSpawnRate{25};*/
	float weaponPUSpawnRate{ 2 };
	float shieldPUSpawnRate{ 2 };
	float companionSpawnRate{ 5 };

	float lonerDeltaTime{0};
	float rusherDeltaTime{0};
	float weaponPUDeltaTime{3};
	float shieldPUDeltaTime{1};
	float companionDeltaTime{5};
	int windowWidth{};
	int windowHeight{};
	bool needCompanion = true;

	Spaceship* playerReference{nullptr};

	std::vector<Enemy*> levelEnemies{};
	std::vector<Entity*> levelPowerUps{};
};

