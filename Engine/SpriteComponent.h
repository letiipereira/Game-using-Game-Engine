#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string textureid, std::string filePath, float spriteRotation, int layer = 0, bool needsCut = false, int currentRow = 1, int currentCol = 1, int totalRows = 1, int totalCol = 1);
	~SpriteComponent() override {};

	bool Init() override final;

	void Draw() override final;
	
	void Update() override final;

	inline int GetLayer() 
	{
		return myLayer;
	}

private:
	std::string myFilePath{};
	Transform* transform{ nullptr };
	std::string textureID{};
	std::string newTextureID{};
	class Texture* texture{ nullptr };
	
	int width{0};
	int height{0};

	float rotation{0};

	int myLayer{0};
	bool flip{ false };
	bool willBeCut{ false };
	int colCurrent{1};
	int colTotal{1};
	int rowCurrent{1};
	int rowTotal{1};
};