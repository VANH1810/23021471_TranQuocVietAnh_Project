#pragma once
#include "Config.cpp"

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const string& texture, SDL_Renderer* ren);
        static void Draw(SDL_Renderer* ren, SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
    private:
    
    
};