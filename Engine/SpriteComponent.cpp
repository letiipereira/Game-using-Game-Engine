#include "SpriteComponent.h"
#include "TextureManager.h"
#include "SDL.h"

SpriteComponent::SpriteComponent(std::string textureid, std::string filePath, float spriteRotation, int layer, bool needsCut, int currentRow, int currentCol, int totalRows, int totalCol)
{
	textureID = textureid;
	myFilePath = filePath;
	rotation = spriteRotation;
	myLayer = layer;
	willBeCut = needsCut;
	rowCurrent = currentRow;
	colCurrent = currentCol;
	rowTotal = totalRows;
	colTotal = totalCol;
}

bool SpriteComponent::Init()
{
	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(textureID, myFilePath);
	return true;
}

void SpriteComponent::Draw()
{
	if (!willBeCut)
	{
		TextureManager::GetInstance()->DrawTexture(textureID, transform, rotation, flip);
	}
	else
	{
		std::string newTextureID{};

		if (TextureManager::GetInstance()->GetTexture(textureID) != nullptr)
		{
			int count = 1;
			newTextureID = textureID + "." + std::to_string(count);

			while (TextureManager::GetInstance()->GetTexture(textureID) != nullptr)
			{
				++count;
				newTextureID = textureID + "." + std::to_string(count);
			}
		}
		else
		{
			newTextureID = textureID;
		}

		std::cout << TextureManager::GetInstance()->GetTexture(newTextureID) << std::endl;
		TextureManager::GetInstance()->DrawFrame(newTextureID, transform, rowCurrent, colCurrent, rowTotal, colTotal, 0, false);
	}
	
}

void SpriteComponent::Update()
{
	transform = &entity->GetComponent<Transform>();
}
