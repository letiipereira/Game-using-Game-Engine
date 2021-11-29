#pragma once
#include "GameEngine.h"
#include "Pawn.h"

class Spaceship : public Pawn
{
public:
	Spaceship();
	~Spaceship() {};

	enum Movement { move_right, move_left, move_up, move_down };

private:
	float moveSpeed = 300.0f;
	float uniform = 0.7071f;
	float spaceshipXDir{};
	float lastPosX{};
	float time{};
	float bulletDeltaTime{0.1};
	float bulletCoolDown{0.15};

	int animDir{ 0 };
	class Animator myAnimator{};
	Animation* moveRight{};
	Animation* moveLeft{};
	Animation* idle{};

	void OnKeyDown(std::string keycode) override;
	void OnKeyUp(std::string key) override;
	void OnButtonDown(std::string button) override;
	void OnButtonUp(std::string button) override;
	void Move();
	void ControllerMove();
	void Attack();
	void CheckKeyState() override;

	void Update() override final;
	void Init() override final;
	void ShipAnimation();

	std::map<std::string, bool> KeyboardKeystate;
	std::map<std::string, bool> GamepadButtonstate;
};
#pragma once