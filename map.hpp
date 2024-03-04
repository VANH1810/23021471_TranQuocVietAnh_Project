#pragma once
#include "Config.cpp"
#include "Layer.cpp"

class Map
{
    public:
        Map(const string &name, SDL_Renderer* ren, const json& map);
        ~Map();
        void render();
        

    private:
        int mapWidth;
        int mapHeight;
        int tileWidth;
        int tileHeight;
        string mapName;
        json* mapData;
        TileSet* tileSet;
        vector <Layer*> layers;
        SDL_Renderer *renderer;
        
        

};