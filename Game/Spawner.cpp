#include "Spawner.h"
#include "Loner.h"

Spawner::Spawner()
{
	
}
Spawner::~Spawner()
{
}

void Spawner::Update()
{
	Entity::Update();

	lonerDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (lonerDeltaTime > lonerSpawnRate)
	{
		SpawnLoner();
		
	}
}

void Spawner::Init()
{
	Entity::Init();
}

void Spawner::SpawnLoner()
{
	Loner* newLoner = new Loner;
	levelEnemies.push_back(newLoner);
	lonerDeltaTime = 0;
}

void Spawner::SpawnRusher()
{

}
