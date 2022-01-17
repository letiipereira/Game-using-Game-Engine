#pragma once
#include "GameEngine.h"
#include "Pawn.h"
#include <vector>
#include <unordered_map>
#include "Companion.h"

struct Vector2DCompare
{
	bool operator() (const Vector2D& lhs, const Vector2D& rhs) const
	{
		return lhs.Y < rhs.Y;
	}
};

class Spaceship : public Pawn
{
public:
	Spaceship();
	~Spaceship() {};

	enum Movement { move_right, move_left, move_up, move_down };

	int maxHealth{};

	void ApplyShield(int shieldValue);
	void ApplyDamage(int damageReceived);
	void ChangeBulletLevel(bool willIncrease);
	void RemoveCompanion(Companion* companion);

	void WasHit(Entity* collidedObject) override;

	std::map<Vector2D, Companion*, Vector2DCompare> GetCompanionList() { return companionList; }
	

private:
	float moveSpeed = 300.0f;
	float uniform = 0.7071f;
	float spaceshipXDir{};
	float lastPosY{};
	float time{};
	float bulletDeltaTime{0.1};
	float bulletCoolDown{0.15};

	int maxLifes{};
	int currentLifes{};
	int health{};
	int currentCompanions{};
	int maxCompanions{};
	int bulletLevel{};
	int bulletMinLevel{};
	int bulletMaxLevel{};

	int animDir{0};
	class Animator myAnimator{};
	Animation* moveUp{};
	Animation* moveDown{};
	Animation* idle{};

	void OnKeyDown(std::string keycode) override;
	void OnKeyUp(std::string key) override;
	void OnButtonDown(std::string button) override;
	void OnButtonUp(std::string button) override;
	void Init() override final;
	void Update() override final;
	void Move();
	void Attack();
	void CheckKeyState() override;
	void IncreaseCompanionCount();
	void DecreaseCompanionCount();
	bool HasMaxCompanions();

	void ShipAnimation();

	std::map<std::string, bool> KeyboardKeystate;
	std::map<std::string, bool> GamepadButtonstate;
	std::map<Vector2D, Companion*, Vector2DCompare> companionList{};
};
#pragma once