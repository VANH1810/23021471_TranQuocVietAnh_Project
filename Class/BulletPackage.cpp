#pragma once

#include "BulletPackage.hpp"

BulletPackage::~BulletPackage()
{}

BulletPackage::BulletPackage(int xpos, int ypos, SDL_Texture* bulletIcon, SDL_Renderer* ren, const string TypeOfBullet)
{
    renderer = ren;
    bulletIconTexture = bulletIcon;
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 512;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 8;
    destRect.h = srcRect.h / 8;
    type = TypeOfBullet;
}
void BulletPackage::draw()
{
    TextureManager::Draw(renderer, bulletIconTexture, srcRect, destRect);
}
