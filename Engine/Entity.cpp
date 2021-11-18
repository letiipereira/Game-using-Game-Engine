#include "Entity.h"
#include "Level.h"


Entity::Entity()
{

this->AddCompoonent<Transform>();
GameEngine::GetInstance()->GetActiveLevel()->AddEntity(this);

}

template<typename T, typename... TArgs>
T& Entity::AddCompoonent(TArgs&&... args)
{
	T* comp(new T(std::forward<TArgs>(args)...));

	std::unique_ptr<Component> uptr{ comp };
	components.emplace_back(std::move(uptr));
	comp->entity = this;

	if (comp->Init())
	{
		compList[GetComponentTypeID<T>()] = comp;
		compBitset[GetComponentTypeID<T>()] = true;
		comp->entity = this;
		return *comp;
	}

	return *static_cast<T*>(nullptr);
}

template<typename T>
T& Entity::GetComponent() const {
	auto ptr(compList[GetComponentTypeID<T>()]);
	return *static_cast<T*>(ptr);
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

