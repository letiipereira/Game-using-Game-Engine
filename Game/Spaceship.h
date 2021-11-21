#pragma once
#include "GameEngine.h"
#include "Pawn.h"

class Spaceship : public Pawn
{
private:
	float moveSpeed = 500.0f;
	float uniform = 0.7071f;

	void Move(MovementType movement, float deltaTime) override;

	void Attack() override;
};
#pragma once