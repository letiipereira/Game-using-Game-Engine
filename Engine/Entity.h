#pragma once

#include "GameEngine.h"
#include "ECS.h"
#include <vector>
#include "Component.h"
#include <memory>
#include "Transform.h"
#include "Level.h"

class Entity
{
public:

	Entity(){

		this->AddCompoonent<Transform>();
		GameEngine::GetInstance()->GetActiveLevel()->AddEntity(this);

	}
	virtual ~Entity() {};

	template<typename T, typename... TArgs>
	inline T& AddCompoonent(TArgs&&... args)
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
	inline T& GetComponent() const {
		auto ptr(compList[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template <typename T>
	inline bool HasComponent() const {
		return compBitset[GetComponentTypeID<T>()];
	}

	inline bool IsActive() const {
		return active;
	}

	inline void Destroy() {
		active = false;
	}

	inline void Draw() {
		for (auto& comp : components)
		{
			comp->Draw();
		}
	}

	inline void Update()
	{
		for (auto& comp : components)
		{
			comp->Update();
		}
	}

private:

	bool active{};
	ComponentList compList{};
	ComponentBitset compBitset{};
	std::vector<std::unique_ptr<Component>> components;
};