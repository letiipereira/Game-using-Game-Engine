#include "Entity.h"
#include "Level.h"

Entity::Entity()
{
	level = GameEngine::GetInstance()->GetActiveLevel();
	level->AddEntity(this);
	this->AddComponent<Transform>();
}

Entity::~Entity()
{
	for (auto& comp : components)
	{
		comp->~Component();
		comp.release();
	}
}

//void Entity::AddGroup(Group mGroup)
//{
//	groupBitset[mGroup] = true;
//	level->AddToGroup(this, mGroup);
//}


void Entity::Draw()
{
	for (auto& comp : components)
	{
			comp->Draw();
	}
}

void Entity::Update()
{
	for (auto& comp : components)
	{
		comp->Update();
	}
}

