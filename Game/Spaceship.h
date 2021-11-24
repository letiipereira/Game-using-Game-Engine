#pragma once
#include "GameEngine.h"
#include "Pawn.h"

class Spaceship : public Pawn
{
public:
	Spaceship();
	~Spaceship()
	{
		delete moveLeft, moveRight, idle;
	}

private:
	float moveSpeed = 300.0f;
	float uniform = 0.7071f;
	float spaceshipXDir{};
	float lastPosX{};
	float time{};


	int animDir{ 0 };
	class Animator myAnimator{};
	Animation* moveRight{};
	Animation* moveLeft{};
	Animation* idle{};

	void Move(MovementType movement) override;
	void Attack() override;
	void Update() override final;
	void Init() override final;
	void ShipAnimation();

};
#pragma once