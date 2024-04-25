#pragma once
#include "map.hpp"

Map::Map(const string &name, SDL_Renderer* ren, const json& map){
    
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
    for (auto layer: layers)
    {
        delete layer;
    }
    if (tileSet != NULL)
        delete tileSet;
}

void Map::render()
{
    for (auto layer: layers)
    {
        layer->render(tileSet, renderer);
    }
}

void Map::setCollisionByProperty(json* properties, bool istrue = true){
    if (tileSet == NULL)
    {
        cerr << "No tileset found" << endl;
        return;
    }
    for (auto tile: tileSet->tiles)
    {
        Tile* temp = tile.second;
        unordered_map <string, json> props;
        for (auto property: temp->properties)
        {
            props[property["name"]] = property["value"];
        }
        bool match = true;
        for (auto property: properties->items())
        {
                auto it = props.find(property.key());
                if (it == props.end() || it->second != property.value())
                {
                    match = false;
                    break;
                }
        }
        if (match)
        {
                //cerr << "Setting collision for tile " << temp->id << endl;
                temp->isCollidable = istrue;
        }           
    }

}