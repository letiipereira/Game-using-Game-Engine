#include "Level.h"
#include <memory>
#include "SpriteComponent.h"
#include <vector>
#include "TextureManager.h"
#include <algorithm>

void Level::Draw()
{
	TextureManager::GetInstance()->Clear();

	std::vector<std::pair<Entity*, int>> store;

	for (Entity* ent : levelEntities)
	{
		if (ent->HasComponent<SpriteComponent>())
		{
			int layer = ent->GetComponent<SpriteComponent>().GetLayer();
			store.push_back(std::pair<Entity*, int>{ ent, layer});
			
		}
		else if (ent->HasComponent<Animator>())
		{
			int layer = ent->GetComponent<Animator>().GetLayer();
			store.push_back(std::pair<Entity*, int>{ent, layer});
		}
		else
		{
			ent->Draw();
		}
	}

	std::sort(store.begin(), store.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (std::pair<Entity*, int> ent : store)
	{
		ent.first->Draw();
	}
}

void Level::AddEntity(Entity* entity)
{
	entity->Init();
	entitiesToAdd.push_back(entity);

}


void Level::EraseEntity(Entity* entity)
{
	//
}

//void Level::AddToGroup(Entity* mEntity, Group mGroup)
//{
//	groupedEntities[mGroup].emplace_back(mEntity);
//}
//
//std::vector<Entity*>& Level::GetGroup(Group mGroup)
//{
//	return groupedEntities[mGroup];
//}

void Level::Update()
{
	for (Entity* ent : levelEntities)
	{
		if (ent == nullptr)
			continue;
		ent->Update();
	}
}

void Level::Refresh()
{
	std::vector<Entity*> entitiesToDelete;

	for (int i = 0; i < levelEntities.size(); i++) // MEMORY LEAK?
	{
		if (!levelEntities[i]->IsActive())
		{
			Entity* thisEntity = levelEntities[i];
			entitiesToDelete.push_back(thisEntity);
			levelEntities.erase(levelEntities.begin() + i);
		}
	}
	
	for (Entity* ent : entitiesToDelete)
	{
		delete ent;
	}
	
	for (Entity* ent : entitiesToAdd)
	{
		levelEntities.push_back(ent);
		ent->Init();
	}

	entitiesToAdd.clear();
}

void Level::Init()
{
	if (levelEntities.size() != 0)
	{
		for (Entity* ent : levelEntities)
		{
			ent->Init();
		}
	}
}


