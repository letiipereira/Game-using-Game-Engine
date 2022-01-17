#include "Loner.h"
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
	
	health = 10;
}

Loner::~Loner()
{
	Enemy::~Enemy();
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

	if (spawnPosY > (GameEngine::GetInstance()->GameWindowHeight() / 2))
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

		if (GetComponent<Transform>().myPosition.Y < -64)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}
	else
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

		if (GetComponent<Transform>().myPosition.Y > GameEngine::GetInstance()->GameWindowHeight() + 64)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}

}

void Loner::Attack()
{
	float x, y{};
	x = GetComponent<Transform>().myPosition.X;
	y = GetComponent<Transform>().myPosition.Y - 40;

	playerPosition = mySpawner->GetPlayerPosition();

	Vector2D missileMovement{};
	missileMovement.X = playerPosition.X - GetComponent<Transform>().myPosition.X;
	missileMovement.Y = (playerPosition.Y + 20.0f) - GetComponent<Transform>().myPosition.Y;

	missileMovement.NormalizeVector();

	Missile* missile = new Missile(x, y, missileMovement.X, missileMovement.Y);
	missileDeltaTime = 0;
}
