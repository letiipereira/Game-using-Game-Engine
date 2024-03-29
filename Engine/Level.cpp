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

	TextureManager::GetInstance()->Render();
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
	//for (auto i(0u); i < maxGroups; i++)
	//{
	//	auto& v(groupedEntities[i]);
	//	v.erase(
	//		std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
	//			{
	//				return !mEntity->IsActive() || mEntity->HasGroup(i);
	//			}),
	//		std::end(v));
	//}

	//std::cout << levelEntities.size()<< std::endl;

	for (int i = 0; i < levelEntities.size(); i++)
	{
		if (!levelEntities[i]->IsActive())
		{
			Entity* thisEntity = levelEntities[i];
			levelEntities.erase(levelEntities.begin()+i);
			delete thisEntity;
		}

	}

	//std::cout << levelEntities.size() << std::endl;

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


