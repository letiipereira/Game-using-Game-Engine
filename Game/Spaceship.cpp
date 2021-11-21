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

