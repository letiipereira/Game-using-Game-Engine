#pragma once

#include <vector>
#include "Entity.h"
#include "Component.h"

constexpr float GRAVITY = 10.0f;

class Rigidbody : public Component
{
public:
	Rigidbody() = default;
	virtual ~Rigidbody() = default;

	Rigidbody(float gravityScale) 
	{
		myGravityScale = gravityScale;
	}

	bool Init() override final;
	void Update() override final;
	//setforce

private:

	float myGravityScale{ 1.0f };
	Transform* transform{ nullptr };
	//drag
	//force
	//velocity

	
};