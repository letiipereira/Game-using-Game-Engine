#include "Entity.h"
#include "Level.h"

Entity::Entity()
{
	level = GameEngine::GetInstance()->GetActiveLevel();
	level->AddEntity(this);
	this->AddComponent<Transform>();

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

//void Entity::Destroy()
//{
//	std::cout << "Collide" << std::endl;
//	delete this;
//}

