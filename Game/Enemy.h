#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy();
	~Enemy();

	void Update() override;
	void Init() override;

	void ApplyDamage(float demage);

protected: 

	float health{0};

};

