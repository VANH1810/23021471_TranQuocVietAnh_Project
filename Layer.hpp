#pragma once
#include "Config.cpp"
#include "TileLayer.cpp"
#include "ObjectGroup.cpp"


class Layer
{
    public:
        Layer(json* map);
        ~Layer();
        void render(TileSet* tileSet, SDL_Renderer* renderer);
        string layerName;
        string layerType; 
        SDL_Rect* srcRect;
        int layerId;
        bool visible;
        float layerOpacity;
        TileLayer* tileLayer;
    private:
};