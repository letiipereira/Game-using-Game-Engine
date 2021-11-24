#pragma once
#include "Enemy.h"
class Loner : public Enemy
{
public:
	Loner();
	~Loner();

	//void Update() override final;
	void Init() override final;

private:
	Animation* idleLoner{ nullptr };
};

