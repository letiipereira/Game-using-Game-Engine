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
    int count = 0;

    int bigCharCurrentRow = 1;
    int bigCharCurrentCol = 1;

    int smallCharCurrentRow = 1;
    int smallCharCurrentCol = 1;

    for (int character = 0; character < characters.size(); ++character)
    {
        Character newSmallCharacter = {
            characters[character],
            16,
            8,
            smallCharCurrentRow,
            smallCharCurrentCol,
            8
        };

        Character newBigCharacter = {
            characters[character],
            12,
            8,
            bigCharCurrentRow,
            bigCharCurrentCol,
            16
        };

        smallCharacters.insert(std::pair<char, Character>(characters[character], newSmallCharacter));
        bigCharacters.insert(std::pair<char, Character>(characters[character], newBigCharacter));

        if (bigCharCurrentCol < 8 || smallCharCurrentCol < 8)
        {
            ++bigCharCurrentCol;
            ++smallCharCurrentCol;
        }
        else if (bigCharCurrentCol >= 8 || smallCharCurrentCol >= 8)
        {
            bigCharCurrentCol = 1;
            smallCharCurrentCol = 1;

            ++bigCharCurrentRow;
            ++smallCharCurrentRow;
        }
    }

    
}

TextureManager::~TextureManager()
{
    std::map<std::string, Texture*>::iterator it;
    for (it = textureMap.begin(); it != textureMap.end(); ++it)
    {
        delete it->second;
    }

    textureMap.clear();
        
}

void TextureManager::DrawTexture(std::string id, Transform* transform, float angle, bool flipHor) // could implement flip vertical and the rotation relkated to a especific point
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

    
    Renderer::GetInstance()->Draw(transform, current, angle);
    
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

void TextureManager::DrawFrame(std::string id, Transform* transform, int rowCurrent, int colCurrent, int rowTotal, int colTotal, float angle, bool flipHor)
{
    Texture* current = GetTexture(id);

    if (current == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;

        return;
    }

    Renderer::GetInstance()->Draw(transform, current, static_cast<float>(angle), static_cast<float>(colCurrent), static_cast<float>(rowCurrent), static_cast<float>(colTotal), static_cast<float>(rowTotal), flipHor);
}

void TextureManager::DrawText(std::string textToRender, CharacterType type, float angle, float x, float y, int layer, std::string id)
{
  

    switch (type)
    {
    case CharacterType::small:
    {
        std::vector<Entity*> letters{};

        for (char& character : textToRender)
        {
            Character ch = smallCharacters[character];
            
            // now advance cursors for the next character
            x += ch.Advance;

            Transform pos;
            pos.myPosition.X = x;
            pos.myPosition.Y = y;

            DrawFrame(id, &pos , ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, 0, false);
        }

        break;
    }

    case CharacterType::big:
    {
        std::vector<Entity*> letters{};

        for (char& character : textToRender)
        {
            Character ch = bigCharacters[character];

            std::string textureID = std::to_string(character);

            // now advance cursors for the next character
            x += ch.Advance;

            Transform pos;
            pos.myPosition.X = x;
            pos.myPosition.Y = y;

            DrawFrame(id, &pos, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, 0, false);
        }

        break;
    }
    default:
        break;
    }
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
