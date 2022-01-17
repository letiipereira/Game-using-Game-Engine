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

	void Init() override final;
	void Update() override final;
	
	void SpawnLoner();
	void SpawnRusher();
	void SpawnDrone();

	void SpawnStoneAsteroid(int size);
	void SpawnMetalAsteroid(int size);

	void SpawnShieldPowerUp();
	void SpawnWeaponPowerUp();
	void SpawnCompanion();

	int ChooseAsterSize();

	std::pair<float,float> SpawnPosAlongX(bool shouldSpawnUp, bool shouldSpawnDown);
	std::pair<float,float> SpawnPosAlongY(bool shouldSpawnRight, bool shouldSpawnLeft);
	

	void CompanionNecessity(bool needCompanion);
	void RemoveEnemy(Enemy* enemy);
	void RemovePowerUp(Entity* powerUp);

	void SetPlayerReference(Spaceship* player);
	Vector2D GetPlayerPosition();

private:

	// window dimentions

	int windowWidth{};
	int windowHeight{};

	// enemy spawn rates 

	float lonerSpawnRate{8};
	float rusherSpawnRate{3};
	float stoneAsterSpawnRate{6};
	float metalAsterSpawnRate{10};
	float droneSpawnRate{ 5 };
	float droneSpawnRateLong{ 10 };
	float droneSpawnRateShort{ 0.4f };

	// enemy delta time 

	float lonerDeltaTime{ 2 };
	float droneDeltaTime{ 5 };
	float rusherDeltaTime{ 1 };
	float stoneAsterDeltaTime{ 2 };
	float metalAsterDeltaTime{ 2 };

	// power up spawn rates

	float weaponPUSpawnRate{15};
	float shieldPUSpawnRate{10};
	float companionSpawnRate{10};

	// power up delta time 

	float weaponPUDeltaTime{ 3 };
	float shieldPUDeltaTime{ 7 };
	float companionDeltaTime{ 5 };

	//drone auxiliar

	bool spawningDronePack{ false };
	int droneCount{ 0 };
	int dronePackNumber{ 8 };
	std::pair<float, float> dronePackSpawnPoint = std::pair<float, float>( 0.0f, 0.0f );

	//companion auxiliar

	bool needCompanion = true;

	// player reference

	Spaceship* playerReference{nullptr};

	// object spawned storages 

	std::vector<Enemy*> levelEnemies{};
	std::vector<Entity*> levelPowerUps{};
};


