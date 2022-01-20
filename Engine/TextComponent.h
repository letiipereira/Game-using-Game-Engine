#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

enum class LetterType { small, big };

class TextComponent : public Component
{
public:
	TextComponent(std::string textToRender, LetterType type, float angle, float x, float y, int layer);
	~TextComponent() override {};

	bool Init() override final;

private:
	std::string text{};
	LetterType textType;
	float rotation;
	int posY{};
	int posX{};
	int currentLayer;
	bool staticText;
};