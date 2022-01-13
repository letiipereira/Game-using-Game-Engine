#pragma once
#include "Entity.h"

class Companion : public Entity
{
public:
	Companion(int posX, int posY, class Spawner* spawner);
	~Companion();

	class Spawner* companionSpawner{ nullptr };
	class Spawner* GetSpawner();

	int maxHealth{};

	void Init();
	void Update();
	void Attack();
	void ApplyShield(int shieldValue);
	void ApplyDamage(int damageReceived);
	void SetDisplacement(Vector2D displacementVector);
	void ChangeBulletLevel(bool willIncrease);
	void TakeCompanion(bool isTaken);
	void SetPlayerReference(class Spaceship* player);
	bool IsTaken();

private:
	int health{};
	int bulletLevel{};
	int bulletMinLevel{};
	int bulletMaxLevel{};
	int spawnPosX{};
	int spawnPosY{};
	int displacementX{0};
	int displacementY{0};
	bool isTaken{ false };
	float moveSpeed{-0.8f};
	float bulletDeltaTime{ 0.1 };
	float bulletCoolDown{ 0.15 };
	Animation* companionIdle{ nullptr };
	class Spaceship* currentPlayer{};
};
