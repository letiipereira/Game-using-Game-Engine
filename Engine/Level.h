#pragma once
#include "GameEngine.h"
#include <vector>
#include "GameObject.h"

class Level
{
public:

	Level(std::string levelName) {};

	~Level() 
	{
		for (GameObject* obj : levelObjects)
		{ 
			delete obj;
		}
	};

	void addGameObject(GameObject* newGameObject);
	void Update();

private:

	std::vector<GameObject*> levelObjects;

};