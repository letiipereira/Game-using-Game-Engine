#include "Animator.h"
#include "TextureManager.h"
#include "Entity.h"

#include <string>
#include <vector>
#include <iostream>
#include "SDL.h"

Animator::Animator(std::string textureID, std::string filePath, int rowNumber, int columnNumber, int rowEnd, int columnEnd, int rowStart, int colunmStart, int framesPerSeconds, bool horFlip, int layer, bool shouldLoop, bool playfoward, bool playOnStart)
{
	myTextureID = textureID;
	myFilePath = filePath;
	myColumnNumber = columnNumber;
	myRowNumber = rowNumber;
	myRowEnd = rowEnd;
	myColunmEnd = columnEnd;
	myRowStart = rowStart;
	myColunmStart = colunmStart;
	myFramesPerSeconds = framesPerSeconds;
	flip = horFlip;
	myLayer = layer;
	loop = shouldLoop;
	foward = playfoward;
	isActive = playOnStart;
}

bool Animator::Init()
{
	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	SDL_QueryTexture(texture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / myColumnNumber;
	frameHeight = textureHeight / myRowNumber;
	currentColumn = myColunmStart;
	currentRow = myRowStart;
	SetupAnimation();
	if (!foward)
		frameIndex = (frames.size() - 1);
	return true;
}

void Animator::Draw()
{
	TextureManager::GetInstance()->DrawFrame(myTextureID, transform, frameHeight, frameWidth, transform->myRotation, currentFrame.first, currentFrame.second, flip);
}


void Animator::Update()
{
	transform = &entity->GetComponent<Transform>();

	if (isActive)
	{
		time += GameEngine::GetInstance()->GetDeltatime();

		if (time >= (1 / myFramesPerSeconds))
		{
			PlayFoward(foward);
			time = 0;
		}

		currentFrame = frames.at(frameIndex);
		std::cout << currentFrame.first << " " << currentFrame.second << std::endl;
		
	}
	
}

void Animator::SetProperties(std::string textureID, std::string filePath, int rowNumber, int columnNumber, int rowEnd, int columnEnd, int rowStart, int colunmStart, int framesPerSeconds, bool horFlip, int layer, bool shouldLoop, bool playfoward, bool playOnStart)
{
	myTextureID = textureID;
	myFilePath = filePath;
	myColumnNumber = columnNumber;
	myRowNumber = rowNumber;
	myRowEnd = rowEnd;
	myColunmEnd = columnEnd;
	myRowStart = rowStart;
	myColunmStart = colunmStart;
	myFramesPerSeconds = framesPerSeconds;
	flip = horFlip;
	myLayer = layer;
	loop = shouldLoop;
	isActive = playOnStart;

	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	SDL_QueryTexture(texture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / myColumnNumber;
	frameHeight = textureHeight / myRowNumber;

	currentColumn = myColunmStart;
	currentRow = myRowStart;

	SetupAnimation();
}

void Animator::SetupAnimation()
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
				std::cout << " continue" << std::endl;
				continue;
			}
			std::pair<int, int> newFrame { row, col };
			frames.push_back(newFrame);
			
		}
	}
}

void Animator::PlayFoward(bool goingFoward)
{
	if (goingFoward)
	{
		if (frameIndex < (frames.size() - 1))
		{
			++frameIndex;
		}
		else
		{
			if (loop)
			{
				frameIndex = 0;
			}
			else
			{
				isActive = false;
			}
		}
	}
	else
	{
		if (frameIndex > 0)
		{
			--frameIndex;
		}
		else
		{
			if (loop)
			{
				frameIndex = (frames.size() - 1);
			}
			else
			{
				isActive = false;
			}
		}
	}
}

void Animator::PlayFromStart(bool loopAnim, bool playFoward)
{
	foward = playFoward;

	if (foward)
	{
		frameIndex = 0;
	}
	else
	{
		frameIndex = (frames.size() - 1);
	}
	loop = loopAnim;
	isActive = true;
}




