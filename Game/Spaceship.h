#pragma once
#include "GameEngine.h"
#include "Pawn.h"

class Spaceship : public Pawn
{
public:
	Spaceship();
	~Spaceship(){}

private:
	float moveSpeed = 300.0f;
	float uniform = 0.7071f;
	float spaceshipXDir{};
	float lastPosX{};
	float time{};
	float bulletDeltaTime{0.1};
	float bulletCoolDown{0.1};


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