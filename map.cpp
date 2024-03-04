#pragma once
#include "map.hpp"

Map::Map(const string &name, SDL_Renderer* ren, const json& map){
    //construct
    mapName = name;
    Map::renderer = ren;
    mapWidth = map["width"];
    mapHeight = map["height"];
    tileWidth = map["tilewidth"];
    tileHeight = map["tileheight"];
    mapData = new json(map);

    for(auto& layer : map["layers"])
    {
        Layer* tem = new Layer(new json(layer));
        layers.emplace_back(tem);
    }
    
    if (map.find("tilesets") != map.end())
        tileSet = new TileSet(renderer, mapData);
    else
        tileSet = NULL;
    
}

Map::~Map()
{
    delete mapData;
}

void Map::render(){
    for (auto layer: layers)
    {
        layer->render(tileSet, renderer);
    }
}
