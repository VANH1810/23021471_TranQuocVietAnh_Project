#pragma once
#include "Config.cpp"
#include "TileSet.cpp"
#include "Tile.cpp"

class TileLayer
{
    public: 
        TileLayer(json* map);
        ~TileLayer();
        void render(TileSet* tileSet, SDL_Renderer* renderer);
        int getId(int i, int j);
        int layerWidth;
        int layerHeight;
        long long** layerData;
    private: 
};
