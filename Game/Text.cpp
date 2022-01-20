#include "Text.h"
#include "Transform.h"

Text::Text(std::string textToRender, std::string textID, TextType type, float angle, float x, float y, int layer)
{
	switch (type)
	{
	case TextType::small:
		AddComponent<TextComponent>(textToRender, textID, LetterType::small, angle, x, y, layer);
		break;

	case TextType::big:
		AddComponent<TextComponent>(textToRender, textID, LetterType::big, angle, x, y, layer);
		break;

	default:
		break;
	}

	GetComponent<Transform>().myPosition.X = x;
	GetComponent<Transform>().myPosition.Y = y;
}

Text::~Text()
{
	Entity::~Entity();
}

void Text::Init()
{
	Entity::Init();
}

void Text::Update()
{
	Entity::Update();
}