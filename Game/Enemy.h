#pragma once
#include "Entity.h"
#include "Component.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

	void ApplyDamage(float damage);

protected: 

	Animation* die{nullptr};

	bool canReceiveDemage{ true };
	float health{50};
	float time{};
	float loseDamageRate{1};
	class Spawner* mySpawner = nullptr;
};

