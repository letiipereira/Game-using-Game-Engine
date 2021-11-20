#include "SpriteComponent.h"
#include "TextureManager.h"
#include "SDL.h"

SpriteComponent::SpriteComponent(std::string textureid, std::string filePath, int layer)
{
	textureID = textureid;
	myFilePath = filePath;
	myLayer = layer;
}

bool SpriteComponent::Init()
{
	
	transform = &entity->GetComponent<Transform>();
	texture = TextureManager::GetInstance()->LoadTexture(textureID, myFilePath);
	return true;
}

void SpriteComponent::Draw()
{
	
	TextureManager::GetInstance()->DrawTexture(textureID, transform, flip);
}

void SpriteComponent::Update()
{

	transform = &entity->GetComponent<Transform>();
	
}
