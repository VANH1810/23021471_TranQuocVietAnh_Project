#pragma once
#include "TextManager.hpp"  

TTF_Font* TextManager::LoadText(const string& path_font)
{
    if (TTF_Init() != 0) {
        cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
    }

    TTF_Font* font = TTF_OpenFont(path_font.c_str(), 24);
    if(font == nullptr) cerr << "Unable to load font " << path_font << " " << TTF_GetError() << endl;
    return font;
}   

void TextManager::DrawText(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Rect dest, SDL_Color color)
{
    SDL_Texture* tex = nullptr;
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(tempSurface == nullptr) cerr << "Unable to render text " << text << TTF_GetError() << endl;
    else
    {
            tex = SDL_CreateTextureFromSurface(ren, tempSurface);
            if(tex == nullptr) cerr << "Unable to create texture from " << text << SDL_GetError() << endl;
            SDL_FreeSurface(tempSurface);
    }
    
    SDL_RenderCopy(ren, tex, NULL, &dest);
    SDL_DestroyTexture(tex);

}
