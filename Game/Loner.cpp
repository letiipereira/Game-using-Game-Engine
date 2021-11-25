#include "Loner.h"
#include "Spawner.h";

Loner::Loner(int posX, int posY, Spawner* spawner)
{
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	if(spawnPosX < (GameEngine::GetInstance()->GameWindowWidht() / 2))
		idleLoner = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 8, true, 2, true, true, true);
	else
		idleLoner = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 8, false, 2, true, true, true);
	
	GetComponent<Animator>().AddAnimation("idle",idleLoner);
	
	health = 10;
}

Loner::~Loner()
{
	Enemy::~Enemy();
	//std::cout << "DESTROY";
}

void Loner::Init()
{
	Enemy::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Animator>().PlayFromStart("idle", true, true);
	
}

void Loner::Update()
{
	Enemy::Update();

	if (spawnPosX < (GameEngine::GetInstance()->GameWindowWidht() / 2))
	{
		GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht())+10))
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	else
	{
		GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.X < -75)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}

	
}

