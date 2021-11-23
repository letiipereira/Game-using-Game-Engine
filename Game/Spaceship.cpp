#include "Spaceship.h"

Spaceship::Spaceship()
{
	
	health = 100;
}

void Spaceship::Move(MovementType movement)
{
	switch (movement)
	{
		case (MovementType::move_left):
		{
			GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
			}
			break;
		}
		case (MovementType::move_right):
		{
			GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, true);
			}
			break;
		}
		case (MovementType::move_up):
		{
			GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			break;
		}
		case (MovementType::move_down):
		{
			GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			break;
		}

		//spaceshipXDir = GetComponent<Transform>().myPosition.X - posX;
	}
	
}

void Spaceship::Attack()
{

}

void Spaceship::Update()
{
	Pawn::Update();

	time += GameEngine::GetInstance()->GetDeltatime();
	if (time >= 1)
	{
		lastPosX = GetComponent<Transform>().myPosition.X;
		time = 0;
	}
	spaceshipXDir = GetComponent<Transform>().myPosition.X - lastPosX;
	std::cout << spaceshipXDir << std::endl;

	if (spaceshipXDir > 0)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, true);
		}
	}
	else if (spaceshipXDir < 0)
	{
		if (GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveLeft"))
		{
			GetComponent<Animator>().PlayFromStart("moveLeft", false, false);
		}
	}
	else
	{
		if (GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveLeft"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == true)
			{
				GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
				std::cout << "move back\n";
			}
		}
		else if(GetComponent<Animator>().GetCurrentAnimation() == GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			if (GetComponent<Animator>().GetCurrentAnimation()->foward == true)
			{
				GetComponent<Animator>().PlayFromStart("moveRight", false, false);
				GetComponent<Animator>().AddToAnimationQueue("idle", true, true);
				std::cout << "move back\n";
			}
		}

	}
}