#pragma once
#include "GameEngine.h"
#include <vector>
#include "GameObject.h"

class Level
{
public:

	Level() {};

	~Level() 
	{
		for (GameObject* obj : levelObjects)
		{ 
			delete obj;
		}
	};

	void addGameObject(GameObject newGameObject);

private:

	std::vector<GameObject*> levelObjects;

};