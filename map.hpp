#pragma once
#include "Config.cpp"
#include "Layer.cpp"

class Map
{
    public:
        Map(const string &name, SDL_Renderer* ren, const json& map);
        ~Map();
        void render();
        void setCollisionByProperty(json* properties, bool istrue);
        vector <Layer*> layers;

        int mapWidth;
        int mapHeight;
        int tileWidth;
        int tileHeight;
        json* mapData;
        TileSet* tileSet;
        
        
    private:
        string mapName;
        SDL_Renderer *renderer;

};