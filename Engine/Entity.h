#pragma once

#include "GameEngine.h"
#include "ECS.h"
#include <vector>
#include "Component.h"
#include <memory>
#include "Transform.h"

class Entity
{
public:

	Entity();
	virtual ~Entity() {};

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args);

	template<typename T>
	T& GetComponent() const;

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

	void Draw();

	void Update();

private:

	bool active{};
	ComponentList compList{};
	ComponentBitset compBitset{};
	std::vector<std::unique_ptr<Component>> components;
};