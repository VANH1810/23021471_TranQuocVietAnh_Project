#pragma once
#include "Config.cpp"

class Tile
{
    public: 
        Tile(SDL_Texture* _texture, SDL_Rect* _srcRect, json _properties);
        ~Tile();
        void render(SDL_Renderer* renderer, int &i, int &j, int &angle);
        bool isCollidable;
        int id;
        json properties; 

    private:
        
        SDL_Texture* texture;
        SDL_Rect* srcRect;
        
};
