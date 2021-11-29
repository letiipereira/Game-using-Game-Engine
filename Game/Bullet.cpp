#include "Bullet.h"

Bullet::Bullet(int posX, int posY)
{
	AddComponent<Animator>();
	bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 1, 2, 1, 1, 4, false, 3, true, true, true);
	GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
	spawnPosX = posX;
	spawnPosY = posY;
}

Bullet::~Bullet()
{
	Entity::~Entity();
}

void Bullet::Update()
{
	GetComponent<Transform>().myPosition.Y -= 5;
	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);

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
}

void Bullet::Init()
{
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;


	AddComponent<Collider>().AddAttributes("Bullet", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameHeight, true, 0.0f);

}

void Bullet::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() != GetComponent<Collider>().GetId())
	Destroy();
}
