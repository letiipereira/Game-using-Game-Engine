#include "TextureManager.h"
#include <iostream>
#include "Texture.h"
#include "Transform.h"

TextureManager* TextureManager::sInstance{ nullptr };

TextureManager::~TextureManager()
{

    std::map<std::string, Texture*>::iterator it;

    for (it = textureMap.begin(); it != textureMap.end(); it++)
    {
        delete it->second;
    }

    textureMap.clear();
    delete sInstance;
    //delete renderTarget;
    
}

bool TextureManager::DrawTexture(std::string id, Transform* transform, bool flipHor) // could implement flip vertical and the rotation relkated to a especific point
{
    

    if (textureMap[id] == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;
        
        return false;
    }
    else if (textureMap[id]->GetSDLTexture() == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Can't acess sdltexture from texture object" << std::endl;
        return false;
    }
        
    if (renderTarget == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: RenderTarget == nullptr ";
            return false;
    }

    SDL_RendererFlip flip{ SDL_FLIP_NONE };

    if(flipHor)
        flip =  SDL_FLIP_HORIZONTAL ;

    int width{};
    int height{};

    SDL_QueryTexture(textureMap[id]->GetSDLTexture(), nullptr, nullptr, &width, &height);
    
    SDL_Rect scrRect = { 0, 0, width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect{}; // where you wanna draw

    dstRect.x = static_cast<int>(transform->myPosition.X);
    dstRect.y = static_cast<int>(transform->myPosition.Y);
    dstRect.w = static_cast<int>(width * transform->myScale.X);
    dstRect.h = static_cast<int>(height * transform->myScale.Y);

    int sucess = SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, transform->myRotation, nullptr, flip);
    //std::cout << "TextureManager::DrawTexture: SDL_RenderCopyEx: " << SDL_GetError() << std::endl;
    //SDL_RenderPresent(renderTarget);
    return (sucess == 0) ? true : false;
}

void TextureManager::Render()
{
    SDL_RenderPresent(renderTarget);
}

void TextureManager::Clear()
{
    SDL_RenderClear(renderTarget);
}

void TextureManager::DropTexture(std::string id)
{
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::DrawFrame(std::string id, Transform* transform, int width, int height, double angle, int row, int frame, bool flipHor)
{
    SDL_RendererFlip flip{ SDL_FLIP_NONE };

    if (flipHor)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_Rect scrRect = { width*(frame-1), height*(row-1), width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect = { static_cast<int>(transform->myPosition.X),static_cast<int>(transform->myPosition.Y), static_cast<int>(width * transform->myScale.X), static_cast<int>(width * transform->myScale.X) }; // where you wanna draw
    SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, angle, 0, flip);
}

Texture* TextureManager::GetTexture(std::string id)
{
    return (textureMap.count(id)>0) ? textureMap[id] : nullptr;
}

Texture* TextureManager::LoadTexture(std::string id, std::string filePath)
{
    Texture* newTexture = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

    if (surface == nullptr)
        std::cout << "Error Loading texture, null surface " << std::endl;

    else
    {
        
        if (renderTarget == nullptr)
            std::cout << "TextureManager::LoadTexture" << SDL_GetError() << std::endl;
        
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        
        if (textureMap[id] == nullptr)
        {
            newTexture = new Texture(surface, renderTarget);
            textureMap[id] = newTexture; // problemas de overwrite (?)
            if (newTexture == nullptr)
                std::cout << "Error creating texture from surface" << std::endl;
        }
        else
            std::cout << "Error Id already exists" << std::endl;
    }

    SDL_FreeSurface(surface);

    return newTexture;
}
