#pragma once
#include "Entity.h"

class Pawn : public Entity
{

public:

	Pawn();

	enum class MovementType { move_right, move_left, move_up, move_down };

	virtual void Move(MovementType movement, float deltaTime) {};

	virtual void Attack() {};

};
#pragma once
