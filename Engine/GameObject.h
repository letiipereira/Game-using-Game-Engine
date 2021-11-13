#pragma once
#include "GameEngine.h"
#include <vector>


class GameObject {

public:

	GameObject(std::string myName) // cria um objeto com todos os valores em default
	{
		name = myName;
	}; 

	GameObject(std::string myName, float posX, float posY) // especifica apenas a posiçao 
	{
		name = myName;
		position.at(0) = posX;
		position.at(1) = posY;
	};

	GameObject(std::string myName, float posX, float posY, float rotX, float rotY) // especifica apenas a posição e rotação 
	{
		name = myName;

		position.at(0) = posX;
		position.at(1) = posY;

		rotation.at(0) = rotX;
		rotation.at(1) = rotY;
	};

	GameObject(std::string myName, float posX, float posY, float rotX, float rotY, float sclX, float sclY) // especifica apenas a posição, rotação e scale
	{
		name = myName;

		position.at(0) = posX;
		position.at(1) = posY;

		rotation.at(0) = rotX;
		rotation.at(1) = rotY;

		scale.at(0) = sclX;
		scale.at(1) = sclY;
	};



	virtual ~GameObject() {};

	virtual void Start();
	virtual void Update();
	

	std::vector<float> GetPosition();
	std::vector<float> GetRotation();
	std::vector<float> GetScale();
	void ChangePosition(float posX, float posY);
	std::string GetName();
	//Update texture?

private:
	
	std::vector<float> position{0,0};
	std::vector<float> rotation{0,0};
	std::vector<float> scale{1,1};
	std::string name{};
	//Reference to the sprite/animation?
};
