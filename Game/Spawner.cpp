#include "Spawner.h"
#include "Loner.h"
#include "Rusher.h"
#include "WeaponPowerUp.h"
#include "ShieldPowerUp.h"
#include "Companion.h"
#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>  

Spawner::Spawner(){}
Spawner::~Spawner()
{
	/*for (Enemy* enemie : levelEnemies)
	{
		delete enemie;
	}*/

	playerReference = nullptr;
}

void Spawner::Update()
{
	Entity::Update();

	lonerDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	rusherDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	weaponPUDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	shieldPUDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (needCompanion)
	{
		companionDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	}
	
	if (lonerDeltaTime > lonerSpawnRate)
	{
		int spawnDir = rand() % 2;
		if (spawnDir == 0)
		{
			int iSecret = (rand() % (windowWidth + 1));
			SpawnLoner(iSecret, 0);
		}
		else if (spawnDir == 1)
		{
			int iSecret = rand() % (windowWidth + 1);
			SpawnLoner(iSecret, windowHeight);
		}
	}

	if (rusherDeltaTime > rusherSpawnRate)
	{
		int spawnDir = rand() % 2;
		if (spawnDir == 0)
		{
			int iSecret = (rand() % (windowHeight + 1));
			SpawnRusher(0, iSecret);
		}
		else if (spawnDir == 1)
		{
			int iSecret = rand() % (windowHeight + 1);
			SpawnRusher(windowWidth, iSecret);
		}
	}

	if (weaponPUDeltaTime > weaponPUSpawnRate)
	{
		int iSecret = rand() % (windowHeight + 1);
		SpawnWeaponPU(windowWidth, iSecret);
	}

	if (shieldPUDeltaTime > shieldPUSpawnRate)
	{
		int iSecret = rand() % (windowHeight + 1);
		SpawnShieldPU(windowWidth, iSecret);
	}

	if (companionDeltaTime > companionSpawnRate)
	{
		int iSecret = rand() % (windowHeight + 1);
		SpawnCompanion(windowWidth, iSecret);
	}
}

void Spawner::RemoveEnemy(Enemy* enemy)
{
	for (int i = 0; i < levelEnemies.size(); i++)
	{
		if (levelEnemies.at(i) == enemy)
		{
			levelEnemies.at(i);
			break;
		}
	}
}

void Spawner::RemovePowerUp(Entity* powerUp)
{
	for (int i = 0; i < levelPowerUps.size(); i++)
	{
		if (levelPowerUps.at(i) == powerUp)
		{
			levelPowerUps.at(i);
			break;
		}
	}
}

void Spawner::SetPlayerReference(Spaceship* player)
{
	playerReference = player;
}

Vector2D Spawner::GetPlayerPosition()
{
	return (playerReference->GetComponent<Transform>().myPosition);
}

void Spawner::Init()
{
	Entity::Init();
	srand(time(NULL));
	windowHeight = GameEngine::GetInstance()->GameWindowHeight();
	windowWidth = GameEngine::GetInstance()->GameWindowWidht();
}

void Spawner::SpawnLoner(int spawnPosX, int spawnPosY)
{
	levelEnemies.push_back(new Loner(spawnPosX, spawnPosY, this));
	lonerDeltaTime = 0;
}

void Spawner::SpawnRusher(int spawnPosX, int spawnPosY)
{
	levelEnemies.push_back(new Rusher(spawnPosX, spawnPosY, this));
	rusherDeltaTime = 0;
}

void Spawner::SpawnWeaponPU(int spawnPosX, int spawnPosY)
{
	levelPowerUps.push_back(new WeaponPowerUp(spawnPosX, spawnPosY, this));
	weaponPUDeltaTime = 0;
}

void Spawner::SpawnShieldPU(int spawnPosX, int spawnPosY)
{
	levelPowerUps.push_back(new ShieldPowerUp(spawnPosX, spawnPosY, this));
	shieldPUDeltaTime = 0;
}

void Spawner::SpawnCompanion(int spawnPosX, int spawnPosY)
{
	levelPowerUps.push_back(new Companion(spawnPosX, spawnPosY, this));
	companionDeltaTime = 0;
}

void Spawner::CompanionNecessity(bool companionNecessity)
{
	needCompanion = companionNecessity;
}
