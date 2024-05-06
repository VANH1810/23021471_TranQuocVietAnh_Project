#pragma once

#include "Layer.hpp"

Layer::Layer(json* map)
{

    layerName = (*map)["name"];
    layerType = (*map)["type"];
    layerId = (*map)["id"];
    visible = (*map)["visible"];
    layerOpacity = (*map)["opacity"];
    srcRect = new SDL_Rect();
    srcRect->x = 0;
    srcRect->y = 0;

    if (layerType == "tilelayer")
    {
        srcRect->w = (*map)["width"];
        srcRect->h = (*map)["height"];
        tileLayer = new TileLayer(map);
    }
}

Layer::~Layer(){
    delete srcRect;

    if (layerType == "tilelayer")
        delete tileLayer;

}

void Layer::render(TileSet* tileSet, SDL_Renderer* renderer)
{
    if (layerType == "tilelayer")
        tileLayer->render(tileSet, renderer);
}