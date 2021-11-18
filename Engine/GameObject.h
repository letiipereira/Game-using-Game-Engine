#pragma once
#include "GameEngine.h"
#include <vector>
#include "Transform.h"
#include "ECS.h"
#include <memory>
#include "Component.h"

class GameObject {

public:

	GameObject(std::string myName, Transform* transform = new Transform())
	{
		name = myName;
		myTransform = transform;
	};

	virtual ~GameObject() 
	{
		delete myTransform;
	};

	virtual void Start();
	virtual void Update();
	void ChangePosition(float posX, float posY);
	std::string GetName();
	//Update texture?

	

private:

	
	Transform* myTransform{};
	std::string textureID{};
	bool flip{ false };
	std::string name{};
	//Reference to the sprite/animation?
};
