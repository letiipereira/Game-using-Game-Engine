#pragma once
#include "GameEngine.h"
#include <vector>
#include "Entity.h"

class Level
{
public:

	Level(std::string levelName) {};

	~Level() {};

	void Draw();
	void Update();
	void Refresh();

	void AddEntity(Entity* entity);
	void EraseEntity(Entity* entity);

private:

	std::vector<Entity*> levelEntities;

};