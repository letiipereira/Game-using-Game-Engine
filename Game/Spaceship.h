#pragma once
#include "GameEngine.h"
#include "Pawn.h"

class Spaceship : public Pawn
{
public:
	Spaceship();

private:
	float moveSpeed = 300.0f;
	float uniform = 0.7071f;

	float spaceshipXDir{};

	void Move(MovementType movement) override;

	void Attack() override;

};
#pragma once