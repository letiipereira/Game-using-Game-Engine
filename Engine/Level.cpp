#include "Level.h"

void Level::Draw()
{
}

void Level::AddEntity(Entity* entity)
{
	levelEntities.push_back(entity);
}

void Level::EraseEntity(Entity* entity)
{
	
}

void Level::Update()
{
	for (Entity* ent : levelEntities)
	{
		ent->Update();
	}
}

void Level::Refresh()
{
}
