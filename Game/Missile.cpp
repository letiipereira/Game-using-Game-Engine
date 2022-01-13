#include "Missile.h"

Missile::Missile(int posX, int posY)
{
	AddComponent<Animator>();
	missileEnAnim = new Animation("missileEnAnim", "assets/EnWeap6.bmp", 1, 8, 1, 8, 1, 1, 4, false, 8, true, true, true);
	die = new Animation("missileExplode", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 8, false, 2, false, true, true);
	GetComponent<Animator>().AddAnimation("missileEnAnim", missileEnAnim);
	spawnPosX = posX;
	spawnPosY = posY;
	hasCollided = false;
}

Missile::~Missile()
{
	
}

void Missile::Update()
{
	Entity::Update();

	if (!hasCollided)
	{
		GetComponent<Transform>().myPosition.Y -= 2;
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
	
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

	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);

	if (hasCollided)
	{
		if (!GetComponent<Animator>().AnimationIsPlaying())
		{
			Destroy();
		}

		GetComponent<Collider>().SetBullet(false);
	}
}

void Missile::Init()
{
	Entity::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("missileExplode", die);

	AddComponent<Collider>().AddAttributes("Missile", this, Collider::BodyType::dynamicBody,
											GetComponent<Transform>().myPosition.X,
											GetComponent<Transform>().myPosition.Y,
											GetComponent<Animator>().GetAnimationByName("missileEnAnim")->frameWidth,
											GetComponent<Animator>().GetAnimationByName("missileEnAnim")->frameHeight, true, 0.0f);		
}

void Missile::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() != "Enemy")
	{
		hasCollided = true;

		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("missileExplode", false, true);
	}
}
