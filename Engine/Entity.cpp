#include "Entity.h"

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