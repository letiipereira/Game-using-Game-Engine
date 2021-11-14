#include "TextureManager.h"
#include <iostream>
#include "Texture.h"

TextureManager* TextureManager::sInstance{ nullptr };

bool TextureManager::DrawTexture(std::string id, int y, int x, int width, int height, double angle, bool flipHor) // could implement flip vertical and the rotation relkated to a especific point
{
    SDL_RenderClear(renderTarget);

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

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(flipHor)
        flip =  SDL_FLIP_HORIZONTAL ;
    
    SDL_Rect scrRect = { 0, 0, width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect = { x,y, width, height }; // where you wanna draw

    int sucess = SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, angle, 0, flip);
    //std::cout << "TextureManager::DrawTexture: SDL_RenderCopyEx: " << SDL_GetError() << std::endl;
    SDL_RenderPresent(renderTarget);
    return (sucess == 0) ? true : false;
}

void TextureManager::DropTexture(std::string id)
{
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::DrawFrame(std::string id, int y, int x, int width, int height, double angle, int row, int frame, bool flipHor)
{
    SDL_RenderClear(renderTarget);

    SDL_RendererFlip flip{ SDL_FLIP_NONE };

    if (flipHor)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_Rect scrRect = { width*frame, height*(row-1), width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect = { x,y, width, height }; // where you wanna draw
    SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, angle, 0, flip);
    SDL_RenderPresent(renderTarget);
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
