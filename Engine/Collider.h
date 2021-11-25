#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>

class Collider : public Component
{
public:
	Collider() {};
	~Collider();

	bool Init() override final;

	void Update() override final;

	void AddAttributes(float objectLocationX, float objectLocationY, float colliderWidth, float colliderHeight, float gravity);

	void SetPosition(float objectLocationX, float objectLocationY);

	void SetVelocity(Vector2D newVelocity);

	Vector2D GetPosition();

private:
	Transform* transform{ nullptr };
	class b2Body* body{};
	float colliderHalfWidth = 0;
	float colliderHalfHeight = 0;
};