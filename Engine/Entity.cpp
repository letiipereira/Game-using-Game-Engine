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
	
}


void Entity::Draw()
{
	if (IsActive())
	{
		for (auto& comp : components)
		{
			comp->Draw();
		}
	}
	else
		return;
	
}

void Entity::Update()
{
	if (IsActive())
	{
		for (auto& comp : components)
		{
			comp->Update();
		}
	}
	else
		return;
}

