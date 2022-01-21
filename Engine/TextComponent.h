#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

enum class LetterType { small, big };

class TextComponent : public Component
{
public:
	TextComponent(std::string textToRender, LetterType type, float angle, float x, float y, int layer, std::string id = "defaultText");
	~TextComponent() override {};

	bool Init() override final;

	void Draw() override final;

	void Update() override final;

	inline int GetLayer() { return currentLayer; }

private:
	std::string text{};
	Transform* transform{ nullptr };
	LetterType textType;
	float rotation;
	int posY{};
	int posX{};
	int currentLayer;
	bool staticText;
};