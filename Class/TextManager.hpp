#pragma once
#include "Config.hpp"

class TextManager
{
    public:
        static TTF_Font* LoadText(const string& path_font);
        static void DrawText(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Rect dest, SDL_Color color);
};