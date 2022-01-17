#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(float posX, float posY, int currentBulletLevel)
{
	AddComponent<Animator>();

	switch (currentBulletLevel)
	{
		case (1):
		{
			//bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 3, 2, 3, 1, 4, false, 3, true, true, true);
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 1, 2, 1, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 10.0f;
			break;
		}

		case (2):
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 2, 2, 2, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 25.0f;
			break;
		}

		case (3):
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 3, 2, 3, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 50.0f;
			break;
		}

		default:
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 1, 2, 1, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 10.0f;
		}
			break;
	}

	spawnPosX = posX;
	spawnPosY = posY;
}

Bullet::~Bullet()
{
	//Entity::~Entity();
}

void Bullet::Update()
{
	Entity::Update();

	GetComponent<Transform>().myPosition.X += 7;

	GetComponent<Collider>().SetVelocity(7/ GameEngine::GetInstance()->GetDeltatime());
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
	Entity::Init();

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Transform>().myRotation = -90.0f;

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameWidth);

	AddComponent<Collider>().AddAttributes("Bullet", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
											colliderWidth, colliderHeight, true, 0.0f);


}

void Bullet::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Enemy" || 
		collidedObject->GetComponent<Collider>().GetId() == "Missile")
	{
		if (collidedObject->GetComponent<Collider>().GetId() == "Enemy")
		{
			Enemy* enemy = static_cast<Enemy*>(collidedObject);
			enemy->ApplyDamage(firePower);
		}

		Destroy();
	}
		
}
