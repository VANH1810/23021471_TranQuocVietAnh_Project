#pragma once
#include "Config.hpp"
#include "TileLayer.cpp"


class Layer
{
    public:
        Layer(json* map);
        ~Layer();
        void render(TileSet* tileSet, SDL_Renderer* renderer);
        string layerType; 
        SDL_Rect* srcRect;
        int layerId;
        TileLayer* tileLayer;
    private:
        string layerName;
        float layerOpacity;
        bool visible;

};