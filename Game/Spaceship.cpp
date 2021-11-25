#include "Spaceship.h"
#include "Bullet.h"

Spaceship::Spaceship()
{
	health = 100;
	AddComponent<Animator>();

	moveRight = new Animation("moveRight", "assets/Ship1.bmp", 1, 7, 1, 7, 1, 5, 14, false, 6, false, true, false);
	moveLeft = new Animation("moveLeft", "assets/Ship1.bmp", 1, 7, 1, 3, 1, 1, 14, false, 6, false, false, false);
	idle = new Animation("idle", "assets/Ship1.bmp", 1, 7, 1, 4, 1, 4, 7, false, 6, false, false, true);

	GetComponent<Animator>().AddAnimation("moveRight", moveRight);
	GetComponent<Animator>().AddAnimation("moveLeft", moveLeft);
	GetComponent<Animator>().AddAnimation("idle", idle);
}
void Spaceship::Init()
{
	Pawn::Init();
	
	GetComponent<Animator>().PlayFromStart("idle", false, false);

	GetComponent<Transform>().myPosition.X = 100;
	GetComponent<Transform>().myPosition.Y = 100;

	AddComponent<Collider>().AddAttributes(GetComponent<Transform>().myPosition.X,
									       GetComponent<Transform>().myPosition.Y,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameWidth,
										   GetComponent<Animator>().GetAnimationByName("idle")->frameHeight, 0.0f);
}

void Spaceship::Move(MovementType movement)
{
	/*float x{};
	float y{};*/

	switch (movement)
	{
		case (MovementType::move_left):
		{
			if (GetComponent<Transform>().myPosition.X > 0)
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				//GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

				GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

				if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
				{
					GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
				}
			}
			break;
		}
		case (MovementType::move_right):
		{
			if (GetComponent<Transform>().myPosition.X < (GameEngine::GetInstance()->GameWindowWidht() - 64))
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

				GetComponent<Transform>().myPosition.X = GetComponent<Collider>().GetPosition().X;

				if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
				{
					GetComponent<Animator>().PlayFromStart("moveRight", false, true);
				}
			}
			break;
		}
		case (MovementType::move_up):
		{
			if (GetComponent<Transform>().myPosition.Y > 0)
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

				GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
			}
			break;
		}
		case (MovementType::move_down):
		{
			if (GetComponent<Transform>().myPosition.Y < (GameEngine::GetInstance()->GameWindowHeight() - 64))
			{
				GetComponent<Collider>().SetVelocity(moveSpeed * uniform);

				GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform), GetComponent<Transform>().myPosition.Y);

				GetComponent<Transform>().myPosition.Y = GetComponent<Collider>().GetPosition().Y;
			}
			break;
		}

	//spaceshipXDir = GetComponent<Transform>().myPosition.X - posX;

	}

	//Vector2D add{ x,y };
	//add.NormalizeVector();
	//std::cout << static_cast<int>(movement) << std::endl;
	//GetComponent<Transform>().myPosition.X += add.X * moveSpeed;
	//GetComponent<Transform>().myPosition.Y += add.Y * moveSpeed;

	//spaceshipXDir = GetComponent<Transform>().myPosition.X - posX;
}

void Spaceship::Attack()
{
	if (bulletDeltaTime > bulletCoolDown)
	{
		Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 24, GetComponent<Transform>().myPosition.Y + 0);
		bulletDeltaTime = 0;
	}
	
}

void Spaceship::Update()
{
	Pawn::Update();

	time += GameEngine::GetInstance()->GetDeltatime();
	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();           

	if (time >= GameEngine::GetInstance()->GetDeltatime())
	{
		spaceshipXDir = GetComponent<Transform>().myPosition.X - lastPosX;
		time = 0;
	}
	lastPosX = GetComponent<Transform>().myPosition.X;
	
	ShipAnimation();
}



void Spaceship::ShipAnimation()
{
	if (spaceshipXDir > 0 && animDir != 1)
	{
		if ((GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft")))
		{
			GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveRight", false, true);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, true);
		}
		animDir = 1;
	}
	else if (spaceshipXDir < 0 && animDir != -1)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, false);
			GetComponent<Animator>().ClearAnimationQueu();
			GetComponent<Animator>().AddToAnimationQueue("moveLeft", false, false);
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("idle"))
		{
			GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
		}

		animDir = -1;
	}
	else if (spaceshipXDir == 0 && animDir != 0)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == false)
			{

				GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
				GetComponent<Animator>().ClearAnimationQueu();
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
			}
			else
			{
				GetComponent<Animator>().PlayFromStart("idle", false, true);
			}
		}
		else if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == true)
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, false);
				GetComponent<Animator>().ClearAnimationQueu();
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
			}
			else
			{
				GetComponent<Animator>().PlayFromStart("idle", false, true);
			}
		}
		animDir = 0;
	}
}
