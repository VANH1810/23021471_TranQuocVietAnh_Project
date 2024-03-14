#pragma once
#include "Tileset.hpp"

TileSet::TileSet(SDL_Renderer* ren, json* map)
{
    TileSet::renderer = ren;
    if (map->find("tilesets") != map->end())
    {
        for (auto& tileset : (*map)["tilesets"])
        {
            int firstgid = tileset["firstgid"];
            int tilecount = tileset["tilecount"];
            if (tileset.find("image") != tileset.end())
            {
                // Calculate the number of rows (tilecount / columns)
                int columns = tileset["columns"];
                int rows = tilecount / columns;
                int tidewidth = tileset["tilewidth"];
                int tileheight = tileset["tileheight"];
                SDL_Texture* texture = TextureManager::LoadTexture(tileset["image"], renderer);
                unordered_map <int, json> properties;
                if (tileset.find("tiles") != tileset.end())
                {
                    for (auto& tile : tileset["tiles"])
                    {
                        properties[tile["id"]] = tile["properties"];
                    }
                }
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        int id = firstgid + i * columns + j;
                        SDL_Rect* srcRect = new SDL_Rect({j * tidewidth, i * tileheight, tidewidth, tileheight});
                        if (tileset.find("tiles") != tileset.end())
                        {
                            if (properties.find(id) != properties.end())
                            {
                                tiles[id] = new Tile(texture, srcRect, properties[id]);
                            }
                            else
                            {
                                tiles[id] = new Tile(texture, srcRect);
                            }
                        }
                        else
                        {
                            tiles[id] = new Tile(texture, srcRect);
                        }
                        tiles[id]->id = id;
                        tiles[id]->isCollidable = false;
                    }
                }
            }
            else cerr << "No found Image" << endl;
        }
    }
    
    else cerr << "No found Tileset" << endl;
}

TileSet::~TileSet()
{
    for (auto tile : tiles)
    {
        delete tile.second;
    }
}
