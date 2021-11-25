#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy();
	~Enemy() override;

	void Update() override;
	void Init() override;

	void ApplyDamage(float demage);

protected: 

	float health{10};
	Animation* die{ nullptr };
	float time{};
	float loseDemageRate{1};
};

