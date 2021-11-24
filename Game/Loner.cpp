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

}

void Loner::Init()
{
	Enemy::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	std::cout << "loner init\n";

}

void Loner::Update()
{
	Enemy::Update();

	if (spawnPosX < (GameEngine::GetInstance()->GameWindowWidht() / 2))
	{
		GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht())+10))
		{
			std::cout << "Loner should be destroyed" << std::endl;
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	else
	{
		GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		if (GetComponent<Transform>().myPosition.X < -75)
		{
			std::cout << "Loner should be destroyed" << std::endl;
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}

	
}

