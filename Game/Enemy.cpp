#include "Enemy.h"

Enemy::~Enemy()
{
	Entity::~Entity();
	/*std::cout << "DESTROY ENEMY";*/

}
Enemy::Enemy()
{
	die = new Animation("enemydie", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 8, false, 2, false, true, true);
}

void Enemy::Update()
{
	Entity::Update();

	/*time += GameEngine::GetInstance()->GetDeltatime();
	if (time > loseDemageRate && health > 0)
	{
		ApplyDamage(5);
		time = 0;
	}*/
	
	if (health <= 0 && !GetComponent<Animator>().AnimationIsPlaying())
	{
		Destroy();

	}

	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
}

void Enemy::Init()
{
	Entity::Update();
	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("enemydie", die);
}

void Enemy::ApplyDamage(float demage)
{
	health -= demage;
	if (health <= 0)
	{
		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("enemydie", false, true);
	}
}
