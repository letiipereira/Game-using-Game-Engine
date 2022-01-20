#pragma once
#include "Entity.h"

enum class TextType { small, big };

class Text : public Entity
{
public:
	Text(std::string textToRender, std::string textID, TextType type, float angle, float x, float y, int layer, bool isStatic);

	~Text() override;

	void Init() override;;
	void Update() override;

private:
};