#pragma once

#include "Layer.hpp"
#include "TileSet.cpp"

Layer::Layer(json* map){
    //construct
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

    else if (layerType == "objectgroup")
        delete objectGroup;
    
}

void Layer::render(TileSet* tileSet, SDL_Renderer* renderer){
    if (layerType == "tilelayer")
        tileLayer->render(tileSet, renderer);
    
}