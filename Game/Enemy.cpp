#include "Enemy.h"

Enemy::~Enemy()
{

}
Enemy::Enemy()
{
}

void Enemy::Update()
{
	Entity::Update();

}

void Enemy::Init()
{
	Entity::Update();

}

void Enemy::ApplyDamage(float demage)
{
	health -= demage;
	if (health <= 0)
	{
		Destroy();
	}
}
