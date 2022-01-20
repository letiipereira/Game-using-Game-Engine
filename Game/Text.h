#pragma once
#include "Entity.h"

enum class TextType { small, big };

class Text : public Entity
{
public:
	Text(std::string textToRender, std::string textID, TextType type = TextType::small, float angle = 0, float x = 0, float y = 0, int layer = 10);
	~Text() override;

	void Init() override;;
	void Update() override;

private:
};