#include "Spaceship.h"

Spaceship::Spaceship()
{
	health = 100;
}

void Spaceship::Move(MovementType movement)
{
	float posX{ GetComponent<Transform>().myPosition.X };

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

	}

	spaceshipXDir = GetComponent<Transform>().myPosition.X - posX;

	// if possible move the code below to update function 

	/*if (spaceshipXDir > 0)
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
			GetComponent<Animator>().PlayFromStart("moveLeft", false, true);
		}
		else if(GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, false);
		}
	}*/
}

void Spaceship::Attack()
{

}