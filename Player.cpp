#pragma once

#include "Player.hpp"

Player::Player(const string & texture, SDL_Renderer* ren)
{
    renderer = ren;
    PlayerTexture = TextureManager::LoadTexture(texture, ren);
    
}
Player::~Player()
{
    SDL_DestroyTexture(PlayerTexture);
}

void Player::update()
{
    xpos = 256;
    ypos = 256;
    srcRect.h = 128;
    srcRect.w = 128;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / SCALEDOWN;
    destRect.h = srcRect.h / SCALEDOWN;
}

void Player::render()
{
    SDL_RenderCopy(renderer, PlayerTexture, &srcRect, &destRect);
}