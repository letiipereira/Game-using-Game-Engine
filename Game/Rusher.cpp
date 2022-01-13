#include "Rusher.h"

Rusher::Rusher(int posX, int posY, Spawner* spawner)
{
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	idleRusher = new Animation("idleRusher", "assets/rusher.bmp", 6, 4, 6, 4, 1, 1, 24, false, 3, true, true, true);

	if (spawnPosX > (GameEngine::GetInstance()->GameWindowWidht() / 2))
		GetComponent<Transform>().myRotation = 90.f;
	else
		GetComponent<Transform>().myRotation = -90.f;

	GetComponent<Animator>().AddAnimation("idleRusher", idleRusher);

	health = 10;
}

Rusher::~Rusher() {}

void Rusher::Update()
{
	Enemy::Update();

	if (spawnPosX < (GameEngine::GetInstance()->GameWindowWidht() / 2))
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

		if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht()) + 10))
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	else
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

		if (GetComponent<Transform>().myPosition.X < -75)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
}

void Rusher::Init()
{
	Enemy::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Animator>().PlayFromStart("idleRusher", true, true);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
										   GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("idleRusher")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("idleRusher")->frameHeight, true, 0.0f);
}
