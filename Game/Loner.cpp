#include "Loner.h"
#include "Spawner.h";
#include "Missile.h"

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

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
										   GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameHeight, true, 0.0f);
	
	health = 5;
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

	missileDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (missileDeltaTime > missileCoolDown && health > 0)
	{
		Attack();
	}

	if (spawnPosX < (GameEngine::GetInstance()->GameWindowWidht() / 2))
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
		}
		
		if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht())+10))
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

void Loner::Attack()
{
	int x, y{};
	x = GetComponent<Transform>().myPosition.X + 32;
	y = GetComponent<Transform>().myPosition.Y + 64;

	Missile* missile = new Missile(x,y);
	missileDeltaTime = 0;
}
