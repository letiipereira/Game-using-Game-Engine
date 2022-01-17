#include "TextureManager.h"
#include <iostream>
#include "Texture.h"
#include "Renderer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Transform.h"

TextureManager* TextureManager::sInstance{ nullptr };

TextureManager::TextureManager()
{
    Renderer::GetInstance()->Init();
}

TextureManager::~TextureManager()
{

    std::map<std::string, Texture*>::iterator it;

    for (it = textureMap.begin(); it != textureMap.end(); it++)
    {
        delete it->second;
    }

    textureMap.clear();
        
}

void TextureManager::DrawTexture(std::string id, Transform* transform, bool flipHor) // could implement flip vertical and the rotation relkated to a especific point
{

    Texture* current = GetTexture(id);

    if (current == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;

        return;
    }

    //int width = current->GetWidth();
    //int height = current->GetHeight();
    //
    //SDL_Rect scrRect = { 0, 0, width, height }; // which part of the image you wanna draw
    //SDL_Rect dstRect{}; // where you wanna draw

    //dstRect.x = static_cast<int>(transform->myPosition.X);
    //dstRect.y = static_cast<int>(transform->myPosition.Y);
    //dstRect.w = static_cast<int>(width * transform->myScale.X);
    //dstRect.h = static_cast<int>(height * transform->myScale.Y);

    
    Renderer::GetInstance()->Draw(transform, current);
    
}

void TextureManager::Render()
{
    
}

void TextureManager::Clear()
{
    Renderer::GetInstance()->Clear();
}

void TextureManager::DropTexture(std::string id)
{
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::DrawFrame(std::string id, Transform* transform, int rowCurrent, int frameCurrent, int rowTotal, int frameTotal, double angle, bool flipHor)
{
    Texture* current = GetTexture(id);

    if (current == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;

        return;
    }
    
    Renderer::GetInstance()->Draw(transform, current, static_cast<float>(frameCurrent), static_cast<float>(rowCurrent), static_cast<float>(frameTotal), static_cast<float>(rowTotal));
}

Texture* TextureManager::GetTexture(std::string id)
{
    return (textureMap.count(id)>0) ? textureMap[id] : nullptr;
}

Texture* TextureManager::LoadTexture(std::string id, std::string filePath)
{
    Texture* newTexture = nullptr;

    if (textureMap[id] == nullptr)
    {
        newTexture = new Texture(filePath);
        textureMap[id] = newTexture; // problemas de overwrite (?)
        if (newTexture == nullptr)
            std::cout << "Error creating texture from surface" << std::endl;
    }
    else
        std::cout << "Error Id already exists" << std::endl;

    return newTexture;
}
