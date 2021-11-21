#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>


class Animation : public Component
{
public:
	Animation(std::string textureID, std::string filePath, int spriteRow, int frameCount, int rowCount, int animSpeed, bool horFlip, int layer = 0);
	~Animation() 
	{
		delete texture;
	};

	bool Init() override final;
	void Draw() override final;
	void Update() override final;

	void SetProperties(std::string textureID, std::string filePath, int spriteRow, int frameCount, int rowCount, int animSpeed, bool horFlip);

	inline int GetLayer()
	{
		return myLayer;
	}

private:

	Transform* transform {nullptr};
	std::string myTextureID{};
	class Texture* texture{ nullptr };
	std::string myFilePath{};

	int myLayer{};
	int mySpriteRow{}, mySpriteFrame;
	int myAnimationSpeed, myFrameCount, myRowCount;
	int textureWidth, textureHeight;
	int frameWidth, frameHeight;
	bool flip{ false };

};

