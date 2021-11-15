#pragma once

struct Position {

	Position(float x, float y) {};

	float x{};
	float y{};
};

struct Rotation {

	Rotation(float x, float y) {};

	float x{};
	float y{};
};

struct Scale {

	Scale(float x, float y) {};

	float x{ 1.0 };
	float y{ 1.0 };
};
struct Transform {

	Transform(Position* position = new Position(0, 0), Rotation* rotation = new Rotation(0, 0), Scale* scale = new Scale(1,1))
	{
		myPosition = position;
		myRotation = rotation;
		myScale = scale;
	}
	~Transform()
	{
		delete myPosition;
		delete myRotation;
		delete myScale;
	}

	Position* myPosition{};
	Rotation* myRotation{};
	Scale* myScale{};

};
