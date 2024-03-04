#pragma once
#include "TextureManager.cpp"
#include "config.cpp"
#include "Tile.cpp"


class TileSet{
    public: 
        TileSet(SDL_Renderer* ren, json* map);
        ~TileSet();
        unordered_map <long long, Tile*> tiles;
        
    private:
        SDL_Renderer* renderer;
};