#include "TextureManager.h"
#include <iostream>
#include "Texture.h"

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
