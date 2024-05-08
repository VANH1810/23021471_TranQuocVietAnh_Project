#pragma once

#include "Config.hpp"
#include "TextureManager.cpp"
class BulletPackage {
private:
    SDL_Texture* bulletIconTexture;
    SDL_Rect srcRect;
    SDL_Renderer* renderer;

public:
    SDL_Rect destRect;
    string type;

    ~BulletPackage();
    BulletPackage(int xpos, int ypos, SDL_Texture* bulletIcon, SDL_Renderer* ren, const string TypeOfBullet);
    void draw();

};