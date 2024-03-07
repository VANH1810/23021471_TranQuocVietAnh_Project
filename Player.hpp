#pragma once
#include "Config.cpp"
#include "TextureManager.cpp"

class Player
{
    public:
        Player(const string & tank_texture, const string &weapon_texture, SDL_Renderer* ren);
        ~Player();
        void render();
        void update();
    private:
        int xpos, ypos;
        SDL_Texture* PlayerTexture;
        SDL_Texture* Weapon;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;

};