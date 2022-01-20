#include "TextComponent.h"
#include "TextureManager.h"
#include "SDL.h"

TextComponent::TextComponent(std::string textToRender, std::string textID, LetterType type, float angle, float x, float y, int layer, bool isStatic)
{
	text = textToRender;
	ID = textID;
	textType = type;
	rotation = angle;
	posX = x;
	posY = y;
	currentLayer = layer;
	staticText = isStatic;

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
	switch (textType)
	{
	case LetterType::small:
	{
		TextureManager::GetInstance()->DrawText(text, ID, CharacterType::small, rotation, posX, posY, currentLayer, staticText);
		break;
	}
		
	case LetterType::big:
	{
		TextureManager::GetInstance()->DrawText(text, ID, CharacterType::big, rotation, posX, posY, currentLayer, staticText);
		break;
	}
		
	default:
		break;
	}	

	return true;
}
