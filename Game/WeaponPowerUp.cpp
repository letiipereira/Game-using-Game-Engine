#include "WeaponPowerUp.h"

WeaponPowerUp::WeaponPowerUp(int posX, int posY, Spawner* spawner)
{
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;

	idlePowerUp = new Animation("idleWeaponPowerUp", "assets/PUWeapon.bmp", 2, 4, 2, 4, 1, 1, 8, true, 3, true, true, true);

	GetComponent<Animator>().AddAnimation("idle", idlePowerUp);

	AddComponent<Collider>().AddAttributes("PowerUp", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X,
		GetComponent<Transform>().myPosition.Y,
		GetComponent<Animator>().GetAnimationByName("idle")->frameWidth,
		GetComponent<Animator>().GetAnimationByName("idle")->frameHeight, true, 0.0f);
}

WeaponPowerUp::~WeaponPowerUp()
{
	PowerUp::~PowerUp();
}

void WeaponPowerUp::Init()
{
	PowerUp::Init();
	moveSpeed = -0.8f;
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Animator>().PlayFromStart("idle", true, true);
}

void WeaponPowerUp::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Spaceship")
	{
		Spaceship* currentPlayer = static_cast<Spaceship*>(collidedObject);
		currentPlayer->ChangeBulletLevel(true);

		Destroy();
	}

	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* playerCompanion = static_cast<Companion*>(collidedObject);
		playerCompanion->ChangeBulletLevel(true);

		Destroy();
	}
}

void WeaponPowerUp::Update()
{
	PowerUp::Update();

	if (GetComponent<Transform>().myPosition.X < -75)
	{
		mySpawner->RemovePowerUp(this);
		Destroy();
	}
}

