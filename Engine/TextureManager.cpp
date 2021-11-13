#include "TextureManager.h"
#include <iostream>
#include "Texture.h"

TextureManager* TextureManager::sInstance{ nullptr };

bool TextureManager::DrawTexture(std::string id, int y, int x, int width, int height, double angle, bool flipHor) // could implement flip vertical and the rotation relkated to a especific point
{
    
    if (textureMap[id] == nullptr)
    {
        std::cout << "Texture id not valid" << std::endl;
        return false;
    }
    if (renderTarget == nullptr)
    {
        renderTarget = SDL_CreateRenderer(GameEngine::GetInstance()->GetWindow()->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (SDL_GetError())
        {
            std::cout << SDL_GetError();
            return false;
        }
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(flipHor)
        flip =  SDL_FLIP_HORIZONTAL ;
    
    SDL_Rect scrRect = { 0, 0, width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect = { x,y, width, height }; // where you wanna draw

    int sucess = SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, angle, 0, flip);
    std::cout << SDL_GetError();
    return (sucess == 0) ? true : false;
}

void TextureManager::DropTexture(std::string id)
{
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::DrawFrame(std::string id, int y, int x, int width, int height, double angle, int row, int frame, bool flipHor)
{
    SDL_RendererFlip flip{ SDL_FLIP_NONE };

    if (flipHor)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_Rect scrRect = { width*frame, height*(row-1), width, height }; // which part of the image you wanna draw
    SDL_Rect dstRect = { x,y, width, height }; // where you wanna draw
    SDL_RenderCopyEx(renderTarget, textureMap[id]->GetSDLTexture(), &scrRect, &dstRect, angle, 0, flip);

}

Texture* TextureManager::LoadTexture(std::string id, std::string filePath)
{
    Texture* newTexture = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

    if (surface == NULL)
        std::cout << "Error Loading texture" << std::endl;

    else
    {

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        if (textureMap[id] == nullptr)
        {
            newTexture = new Texture(surface, renderTarget);
            textureMap[id] = newTexture; // problemas de overwrite (?)
            if (newTexture == NULL)
                std::cout << "Error creating texture from surface" << std::endl;
        }
        else
            std::cout << "Error Id already exists" << std::endl;
    }

    SDL_FreeSurface(surface);

    return newTexture;
}
