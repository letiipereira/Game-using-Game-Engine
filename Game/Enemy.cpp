#include "Enemy.h"
#include "Spaceship.h"
#include "Companion.h"

Enemy::~Enemy()
{
	Entity::~Entity();
}

Enemy::Enemy()
{
	die = new Animation("enemydie", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 15, false, 2, false, true, true);
}

void Enemy::Update()
{
	Entity::Update();
	
	if (health <= 0 && !GetComponent<Animator>().AnimationIsPlaying())
	{
		Destroy();
	}

	if (health <= 0)
	{
		if (!GetComponent<Animator>().AnimationIsPlaying())
		{
			Destroy();
		}

		GetComponent<Collider>().SetBullet(false);
	}
}

void Enemy::Init()
{
	Entity::Init();
	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("enemydie", die);
}

void Enemy::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Spaceship")
	{
		Spaceship* currentPlayer = static_cast<Spaceship*>(collidedObject);
		currentPlayer->ApplyDamage((currentPlayer->maxHealth) / 3);
		currentPlayer->ChangeBulletLevel(false);
		ApplyDamage(health);
	}

	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* playerCompanion = static_cast<Companion*>(collidedObject);
		playerCompanion->ApplyDamage((playerCompanion->maxHealth) / 3);
		playerCompanion->ChangeBulletLevel(false);
		ApplyDamage(health);
	}
}

void Enemy::ApplyDamage(float damage)
{
	health -= damage;

	if (health <= 0)
	{
		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("enemydie", false, true);	
	}
}
