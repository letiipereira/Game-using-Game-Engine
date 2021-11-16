#pragma once
#include "GameObject.h"

class Pawn : public GameObject
{
public:
	enum class MovementType { move_right, move_left, move_up, move_down };

	virtual void Move(MovementType movement) {};

	virtual void Attack() {};
};
