#include "Level.h"

void Level::addGameObject(GameObject* newGameObject)
{
	levelObjects.push_back(newGameObject);
}

void Level::Update()
{
	for (GameObject* obj : levelObjects)
	{
		obj->Update();
	}
}
