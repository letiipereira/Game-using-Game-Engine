#include "Missile.h"

Missile::Missile(int posX, int posY)
{
	AddComponent<Animator>();
	missileEnAnim = new Animation("missileEnAnim", "assets/EnWeap6.bmp", 1, 8, 1, 8, 1, 1, 4, false, 8, true, true, true);
	GetComponent<Animator>().AddAnimation("missileEnAnim", missileEnAnim);
	spawnPosX = posX;
	spawnPosY = posY;
}


Missile::~Missile()
{
	
}

void Missile::Update()
{
	Entity::Update();

	GetComponent<Transform>().myPosition.Y += 5;

	if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht()) + 10) ||
		GetComponent<Transform>().myPosition.X < -10)
	{
		Destroy();
	}
	if (GetComponent<Transform>().myPosition.Y > ((GameEngine::GetInstance()->GameWindowHeight()) + 10) ||
		GetComponent<Transform>().myPosition.Y < -10)
	{
		Destroy();
	}

}

void Missile::Init()
{
	Entity::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
}
