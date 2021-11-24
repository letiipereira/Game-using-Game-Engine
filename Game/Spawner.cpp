#include "Spawner.h"
#include "Loner.h"
#include "Rusher.h"
#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>  

Spawner::Spawner()
{
	
}
Spawner::~Spawner()
{
	for (Enemy* enemie : levelEnemies)
	{
		delete enemie;
	}
}

void Spawner::Update()
{
	Entity::Update();

	lonerDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	rusherDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	
	if (lonerDeltaTime > lonerSpawnRate)
	{
		int spawnDir = rand() % 2;
		if (spawnDir == 0)
		{
			int iSecret = (rand() % (windowHeight + 1));
			SpawnLoner(0, iSecret);
		}
		else if (spawnDir == 1)
		{
			int iSecret = rand() % (windowHeight + 1);
			SpawnLoner(windowWidth, iSecret);
		}
	}
	if (rusherDeltaTime > rusherSpawnRate)
	{
		int spawnDir = rand() % 2;
		if (spawnDir == 0)
		{
			int iSecret = (rand() % (windowWidth + 1));
			SpawnRusher(iSecret, 0);
		}
		else if (spawnDir == 1)
		{
			int iSecret = rand() % (windowWidth + 1);
			SpawnRusher(iSecret, windowHeight);
		}
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
};

void Spawner::Init()
{
	Entity::Init();
	srand(time(NULL));
	windowHeight = GameEngine::GetInstance()->GameWindowHeight();
	windowWidth = GameEngine::GetInstance()->GameWindowWidht();
}

void Spawner::SpawnLoner(int spawnPosX, int spawnPosY)
{
	Loner* newLoner = new Loner(spawnPosX,spawnPosY, this);
	levelEnemies.push_back(newLoner);
	lonerDeltaTime = 0;
	std::cout << "SpawnLoner\n";
}

void Spawner::SpawnRusher(int spawnPosX, int spawnPosY)
{
	Rusher* newRusher = new Rusher(spawnPosX, spawnPosY, this);
	levelEnemies.push_back(newRusher);
	rusherDeltaTime = 0;
	std::cout << "SpawnLoner\n";
}
