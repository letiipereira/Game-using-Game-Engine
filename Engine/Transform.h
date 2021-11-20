#pragma once
#include "Component.h"

struct Position {

	Position(float x, float y) {};

	float x{};
	float y{};
};

struct Scale {

	Scale(float x, float y) {};

	float x{ 1.0 };
	float y{ 1.0 };
};

struct Transform : public Component {

	Transform(Position* position = new Position(0, 0), Scale* scale = new Scale(1,1), float rotation = 0)
	{
		myPosition = position;
		myRotation = rotation;
		myScale = scale;
	}
	virtual ~Transform()
	{
		delete myPosition;
		delete myScale;
	}

	Position* myPosition{};
	Scale* myScale{};
	double myRotation{};

};
