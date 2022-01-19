#pragma once
#include "Entity.h"

enum class LetterType { small, big };

class Icon : public Entity
{
public:
	Icon(std::string textureID, std::string filePath, int posX, int posY, bool needsCut, int rowCurrent, int columnCurrent, int rowTotal, int columnTotal, int layer = 0);

	~Icon() override;

	void Init() override;;
	void Update() override;

private:
};