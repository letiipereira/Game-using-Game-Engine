#pragma once
#include "Entity.h"

enum class TextType { small, big };

class Text : public Entity
{
public:
	Text(std::string text, TextType type = TextType::small, float angle = 0, float posX = 0, float posY = 0, int layerText = 10);
	~Text() override;

	void Init() override;;
	void Update() override;

private:

	std::vector<char> charOrder
	{
	' ', '!', '"', '#', '$', '%', '&', '²',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', ':', ';', '<', '=', '>', '?',
	'©', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '³', ']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
	'x', 'y', 'z', '{', '?', '}', '~', '¤'
	};
};