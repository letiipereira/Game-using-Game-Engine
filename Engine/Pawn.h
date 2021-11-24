#pragma once
#include "Entity.h"

class Pawn : public Entity
{

public:

	Pawn();

	enum class MovementType { move_right, move_left, move_up, move_down };

	virtual void Move(MovementType movement) {};

	virtual void Attack() {};

	int health;

	inline void Update() override { Entity::Update(); };

	inline void Init() override { Entity::Init(); };

};
#pragma once
