#include "Companion.h"
#include "Spaceship.h"
#include "Bullet.h"

Companion::Companion(int posX, int posY, Spawner* spawner)
{
	AddComponent<Animator>();
	maxHealth = 50;
	health = maxHealth;
	bulletLevel = 1;
	bulletMinLevel = 1;
	bulletMaxLevel = 3;
	spawnPosX = posX;
	spawnPosY = posY;
	companionSpawner = spawner;
	companionIdle = new Animation("companionIdle", "assets/clone.bmp", 5, 4, 4, 4, 1, 1, 10, false, 3, true, true, true);

	GetComponent<Animator>().AddAnimation("companionIdle", companionIdle);
}

Companion::~Companion()
{
	Entity::~Entity();
}

Spawner* Companion::GetSpawner()
{
	return companionSpawner;
}

void Companion::Init()
{
	Entity::Init();

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Transform>().myRotation = 90.0f;

	GetComponent<Animator>().PlayFromStart("companionIdle", true, true);

	AddComponent<Collider>().AddAttributes("Companion", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X,
		GetComponent<Transform>().myPosition.Y,
		GetComponent<Animator>().GetAnimationByName("companionIdle")->frameWidth + 10,
		GetComponent<Animator>().GetAnimationByName("companionIdle")->frameHeight + 10, true, 0.0f);
}

void Companion::Update()
{
	Entity::Update();

	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (!isTaken)
	{
		GetComponent<Transform>().myPosition.X += moveSpeed;

		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
	else
	{
		GetComponent<Transform>().myPosition.X = currentPlayer->GetComponent<Transform>().myPosition.X + displacementY;
		GetComponent<Transform>().myPosition.Y = currentPlayer->GetComponent<Transform>().myPosition.Y + displacementX;

		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
	
}

void Companion::Attack()
{
	if (bulletDeltaTime > bulletCoolDown)
	{
		Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 55, GetComponent<Transform>().myPosition.Y, bulletLevel);
		bulletDeltaTime = 0;
	}
}

void Companion::ApplyShield(int shieldValue)
{
	health += shieldValue;

	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Companion::ApplyDamage(int damageReceived)
{
	health -= damageReceived;

	if (health <= 0)
	{
		currentPlayer->RemoveCompanion(this);
	}
}

void Companion::SetDisplacement(Vector2D displacementVector)
{
	displacementX = displacementVector.X;
	displacementY = displacementVector.Y;
}

void Companion::ChangeBulletLevel(bool willIncrease)
{
	if (willIncrease)
	{
		if (bulletLevel != bulletMaxLevel)
		{
			bulletLevel++;
		}
	}
	else if (!willIncrease)
	{
		if (bulletLevel != bulletMinLevel)
		{
			bulletLevel--;
		}
	}
}

void Companion::TakeCompanion(bool willTake)
{
	isTaken = willTake;
}

void Companion::SetPlayerReference(Spaceship* player)
{
	currentPlayer = player;
}

bool Companion::IsTaken()
{
	return isTaken;
}
