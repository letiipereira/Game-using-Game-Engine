#include "TextComponent.h"
#include "TextureManager.h"
#include "SDL.h"

TextComponent::TextComponent(std::string textToRender, LetterType type, float angle, float x, float y, int layer, std::string id)
{
	text = textToRender;
	textType = type;
	rotation = angle;
	posX = x;
	posY = y;
	currentLayer = layer;

	switch (type)
	{
	case LetterType::small:
		textType = LetterType::small;
		break;

	case LetterType::big:
		textType = LetterType::big;
		break;

	default:
		break;
	}
}

bool TextComponent::Init()
{
	transform = &entity->GetComponent<Transform>();
	TextureManager::GetInstance()->LoadTexture("defaultText", "assets/Font8x8.bmp");

	return true;
}

void TextComponent::Draw()
{
	switch (textType)
	{
	case LetterType::small:
	{
		TextureManager::GetInstance()->DrawText(text, CharacterType::small, rotation, posX, posY, currentLayer);

		break;
	}

	case LetterType::big:
	{
		TextureManager::GetInstance()->DrawText(text, CharacterType::big, rotation, posX, posY, currentLayer);
		
		break;
	}

	default:
		break;
	}
}

void TextComponent::Update()
{
	transform = &entity->GetComponent<Transform>();
}