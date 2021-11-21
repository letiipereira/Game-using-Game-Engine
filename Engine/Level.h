#pragma once
#include "GameEngine.h"
#include <vector>
#include "Entity.h"


class Level
{
public:

	Level(std::string levelName) {};

	~Level() 
	{
		for (Entity* ent : levelEntities)
		{
			delete ent;
		}

		levelEntities.clear();
	};

	void Draw();
	void Update();
	void Refresh();

	void AddEntity(Entity* entity);
	void EraseEntity(Entity* entity);
	//void AddToGroup(Entity* mEntity, Group mGroup);
	//std::vector<Entity*>& GetGroup(Group mGroup);

private:
	std::vector<Entity*> levelEntities;
	//std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};