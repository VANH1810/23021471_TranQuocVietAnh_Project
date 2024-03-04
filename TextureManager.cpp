#pragma once
#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const string& texture, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture.c_str());
    SDL_Texture* tex;
    if(tempSurface == nullptr) std::cout << "Unable to load image " <<  texture << IMG_GetError() << std::endl;
    else
    {
        tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        if(tex == nullptr) std::cout << "Unable to create texture from " <<  texture << SDL_GetError() << std::endl;
        SDL_FreeSurface(tempSurface);    
    }
    return tex;
    
}