#include "Enemy.h"

Enemy::~Enemy()
{
	Entity::~Entity();
}

Enemy::Enemy()
{
	die = new Animation("enemydie", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 8, false, 2, false, true, true);
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

	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
}

void Enemy::Init()
{
	Entity::Update();
	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("enemydie", die);
}

void Enemy::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() != GetComponent<Collider>().GetId() &&
		collidedObject->GetComponent<Collider>().GetId() != "Missile")
	{
		ApplyDamage(5);
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
