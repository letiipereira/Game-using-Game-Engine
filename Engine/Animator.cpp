#include "Animator.h"
#include "TextureManager.h"
#include "Entity.h"

#include <string>
#include <vector>
#include <iostream>
#include "SDL.h"


void Animation::Init()
{
	texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	SDL_QueryTexture(texture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / myColumnNumber;
	frameHeight = textureHeight / myRowNumber;
	currentColumn = myColunmStart;
	currentRow = myRowStart;

	SetupAnimation();

	if (!foward)
		frameIndex = (frames.size() - 1);

}


void Animation::SetupAnimation()
{

	for (int row = myRowStart; row <= myRowNumber; ++row)
	{
		for (int col = 1; col <= myColumnNumber; ++col)
		{
			if (row < myRowStart || row > myRowEnd)
			{
				break;
			}
			else if (row == myRowEnd && col > myColunmEnd)
			{
				break;
			}
			else if (row == myRowStart && col < myColunmStart)
			{
				continue;
			}
			std::pair<int, int> newFrame{ row, col };
			frames.push_back(newFrame);

		}
	}
}

bool Animator::Init()
{
	transform = &entity->GetComponent<Transform>();

	return true;
		
}

void Animator::Draw()
{
	TextureManager::GetInstance()->DrawFrame(currentAnimation->myTextureID, transform, currentAnimation->frameHeight, currentAnimation->frameWidth, transform->myRotation, currentFrame.first, currentFrame.second, currentAnimation->flip);
}


void Animator::Update()
{
	transform = &entity->GetComponent<Transform>();
	std::cout << currentAnimation->myTextureID << std::endl;
	if(currentAnimation != nullptr)
	{ 
	
		if (isActive)
		{
			time += GameEngine::GetInstance()->GetDeltatime();

			if (time >= (1 / currentAnimation->myFramesPerSeconds))
			{
				PlayFoward();
				time = 0;
			}

			currentFrame = currentAnimation->frames.at(currentAnimation->frameIndex);
			std::cout << currentFrame.first << " " << currentFrame.second << std::endl;

		}	
	}
	
}

void Animator::AddAnimation(std::string name, Animation* newAnimation)
{
	animations[name] = newAnimation;
	animations[name]->Init();

	if (animations.size() == 1)
		currentAnimation = animations[name];
}

void Animator::PlayFoward()
{
	if (currentAnimation->foward)
	{
		if (currentAnimation->frameIndex < (currentAnimation->frames.size() - 1))
		{
			++currentAnimation->frameIndex;
		}
		else
		{
			if (currentAnimation->loop)
			{
				currentAnimation->frameIndex = 0;
			}
			else
			{
				isActive = false;
			}
		}
	}
	else
	{
		if (currentAnimation->frameIndex > 0)
		{
			--currentAnimation->frameIndex;
		}
		else
		{
			if (currentAnimation->loop)
			{
				currentAnimation->frameIndex = (currentAnimation->frames.size() - 1);
			}
			else
			{
				isActive = false;
			}
		}
	}
}

void Animator::PlayFromStart(std::string animName, bool loopAnim, bool playFoward)
{
	
	currentAnimation = animations[animName];

	currentAnimation->foward = playFoward;

	if (currentAnimation->foward)
	{
		currentAnimation->frameIndex = 0;
	}
	else
	{
		currentAnimation->frameIndex = (currentAnimation->frames.size() - 1);
	}

	currentAnimation->loop = loopAnim;
	isActive = true;
	
}


