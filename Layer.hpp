#pragma once
#include "Config.cpp"
#include "TileLayer.cpp"
#include "ObjectGroup.cpp"


class Layer{
    public:
        Layer(json* map);
        ~Layer();
        void render(TileSet* tileSet, SDL_Renderer* renderer);
    private:
        string layerName;
        string layerType; //tilelayer, objectgroup
        SDL_Rect* srcRect;
        int layerId;
        bool visible;
        float layerOpacity;
        TileLayer* tileLayer;
        ObjectGroup* objectGroup;
};