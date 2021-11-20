#include "Level.h"
#include <memory>
#include "SpriteComponent.h"
#include <vector>
#include <map>
#include "TextureManager.h"

void Level::Draw()
{
	TextureManager::GetInstance()->Clear();

	std::map<int, Entity*> store;

	for (Entity* ent : levelEntities)
	{
		if (ent->HasComponent<SpriteComponent>())
		{
			int layer = ent->GetComponent<SpriteComponent>().GetLayer();
			store[layer] = ent;
			
		}
		else if (ent->HasComponent<Animation>())
		{
			int layer = ent->GetComponent<Animation>().GetLayer();
			store[layer] = ent;
		}
		else
		{
			ent->Draw();
		}
	}

	std::map<int, Entity*>::iterator it;

	for (it = store.begin(); it != store.end(); it++)
	{
		it->second->Draw();
	}

	TextureManager::GetInstance()->Render();
}

void Level::AddEntity(Entity* entity)
{
	levelEntities.push_back(entity);
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

	levelEntities.erase(std::remove_if(std::begin(levelEntities), std::end(levelEntities),
		[](Entity* mEntity)
		{
			return !mEntity->IsActive();
		}),
		std::end(levelEntities));
}


