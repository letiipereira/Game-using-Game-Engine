#include "Rusher.h"

Rusher::Rusher(int posX, int posY, Spawner* spawner)
{
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	if (spawnPosY < (GameEngine::GetInstance()->GameWindowHeight() / 2))
		idleRusher = new Animation("idleRusher", "assets/rusher.bmp", 6, 4, 6, 4, 1, 1, 24, false, 3, true, true, true);
	else
		idleRusher = new Animation("idleRusher", "assets/rusher.bmp", 6, 4, 6, 4, 1, 1, 24, true, 3, true, true, true);

	GetComponent<Animator>().AddAnimation("idleRusher", idleRusher);

	health = 5;
}

Rusher::~Rusher()
{
	//delete idleRusher;
}

void Rusher::Update()
{
	Enemy::Update();

	if (spawnPosY > (GameEngine::GetInstance()->GameWindowHeight() / 2))
	{
		GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.Y < -64)
		{
			std::cout << "Rusher should be destroyed" << std::endl;
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	else
	{
		GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.Y > GameEngine::GetInstance()->GameWindowHeight() + 64)
		{
			std::cout << "Rusher should be destroyed" << std::endl;
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	//std::cout << currentFrame.first << " " << currentFrame.second << std::endl;
}

void Rusher::Init()
{
	Enemy::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	std::cout << "Rusher init\n";
}
