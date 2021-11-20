#include "Animation.h"
#include "TextureManager.h"
#include "Entity.h"

#include <string>
#include <iostream>
#include "SDL.h"

Animation::Animation(std::string textureID, std::string filePath, int spriteRow, int frameCount, int rowCount, int animSpeed, bool horFlip, int layer)
{
	myTextureID = textureID;
	mySpriteRow = spriteRow;
	myFrameCount = frameCount;
	myRowCount = rowCount;
	myAnimationSpeed = animSpeed;
	flip = horFlip;
	myFilePath = filePath;
	myLayer = layer;
}

bool Animation::Init()
{
	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	SDL_QueryTexture(texture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / myFrameCount;
	frameHeight = textureHeight / myRowCount;
	return true;
}

void Animation::Draw()
{
	TextureManager::GetInstance()->DrawFrame(myTextureID, transform->myPosition->x, transform->myPosition->y, frameHeight, frameWidth, transform->myRotation, mySpriteRow, mySpriteFrame, flip);
}


void Animation::Update()
{
	transform = &entity->GetComponent<Transform>();

	int saveFrame = mySpriteFrame;
	
	mySpriteFrame = ((SDL_GetTicks() / myAnimationSpeed) % myFrameCount) + 1;

	if (saveFrame - mySpriteFrame != 0)
	{
		if (mySpriteFrame == 1)
		{
			++mySpriteRow;
		}
		if (mySpriteRow == (myRowCount +1))
		{
			mySpriteRow = 1;
		}
	}

	std::cout << mySpriteFrame << " " << mySpriteRow << std::endl;
}

void Animation::SetProperties(std::string textureID, std::string filePath, int spriteRow, int frameCount, int rowCount, int animSpeed, bool horFlip)
{
	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	SDL_QueryTexture(texture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / myFrameCount;
	frameHeight = textureWidth / myRowCount;
}
