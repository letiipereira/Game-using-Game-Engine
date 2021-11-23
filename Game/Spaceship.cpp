#include "Spaceship.h"

void Spaceship::Move(MovementType movement, float deltaTime)
{
	

	switch (movement)
	{
	case (MovementType::move_left):
	{
		GetComponent<Transform>().myPosition.X -= (moveSpeed * deltaTime * uniform);
		break;
	}
	case (MovementType::move_right):
	{
		GetComponent<Transform>().myPosition.X += (moveSpeed * deltaTime * uniform);		
		break;
	}
	case (MovementType::move_up):
	{
		GetComponent<Transform>().myPosition.Y -= (moveSpeed * deltaTime * uniform);
		break;
	}
	case (MovementType::move_down):
	{
		GetComponent<Transform>().myPosition.Y += (moveSpeed * deltaTime * uniform);
		break;
	}
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
			}
		}
		else if(GetComponent<Animator>().GetCurrentAnimation() != GetComponent<Animator>().GetAnimationByName("moveRight"))
		{
			GetComponent<Animator>().PlayFromStart("moveRight", false, false);
		}
	}
};

