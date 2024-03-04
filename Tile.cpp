#pragma once
#include "Tile.hpp"

Tile::Tile(SDL_Texture* _texture, SDL_Rect* _srcRect, json _properties = json::parse(R"###([])###"))
{
    Tile::texture = _texture;
    Tile::srcRect = _srcRect;
    Tile::properties = _properties;
}

Tile::~Tile()
{
    SDL_DestroyTexture(texture);
    delete srcRect;
}

void Tile::render(SDL_Renderer* renderer, int &i, int &j, int &angle)
{
    int tilewidth = srcRect->w;
    int tileheight = srcRect->h;
    SDL_Rect destRect = {j * tilewidth / SCALEDOWN, i * tileheight / SCALEDOWN, tilewidth / SCALEDOWN, tileheight / SCALEDOWN};
    SDL_RenderCopyEx(renderer, texture, srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}


