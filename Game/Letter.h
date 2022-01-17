#pragma once
#include "Entity.h"

enum class LetterType { small, big };

class Letter : public Entity
{
public:
	Letter(std::string textureID, std::string filePath, int posX, int posY, int rowCurrent, int columnCurrent, int rowTotal, int columnTotal, int layer = 0);

	~Letter() override;

	void Init() override;;
	void Update() override;

private:
};