#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string textureid, std::string filePath, int layer = 0);
	

	virtual ~SpriteComponent() 
	{
		//delete texture;
	};

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
	class Texture* texture{ nullptr };
	
	int width{0};
	int height{0};

	int myLayer{0};
	bool flip{ false };
	int frame{1};
	int frameCount{1};
	int row{1};
	int rowCount{1};
};