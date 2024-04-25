#pragma once
#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const string& texture, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture.c_str());
    SDL_Texture* tex;
    if(tempSurface == nullptr) cerr << "Unable to load image " <<  texture << IMG_GetError() << endl;
    else
    {
        tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        if(tex == nullptr) cerr << "Unable to create texture from " <<  texture << SDL_GetError() << endl;
        SDL_FreeSurface(tempSurface);    
    }
    return tex;
    
}

void TextureManager::Draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, tex, &src, &dest);
}