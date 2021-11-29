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
	float health{5};
	Animation* die{ nullptr };
	float time{};
	float loseDamageRate{1};
};

