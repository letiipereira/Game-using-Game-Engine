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
	/*for (auto& comp : components)
	{
		comp->~Component();
		comp.release();
	}*/

	/*n�o � preciso deletar os componente s�o unique pointer 
	ent�o ja est�o a ser chamados aoutomaticamente*/
}


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

