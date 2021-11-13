#include "TextureManager.h"
#include <iostream>
#include "Texture.h"

Texture* TextureManager::LoadTexture(std::string filePath)
{
    Texture* newTexture = nullptr;

    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());

    if (surface == NULL)
        std::cout << "Error" << std::endl;

    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
        
        newTexture = new Texture(surface);
        textureList.push_back(newTexture);

        //newTexture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (newTexture == NULL)
            std::cout << "Error" << std::endl;
    }

    SDL_FreeSurface(surface);

    return newTexture;
}
