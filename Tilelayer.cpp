#pragma once

#include "TileLayer.hpp"

pair <int, long long> Reformat(long long tileId)
{
    pair <int, long long> angle;
    angle.first = 0;
    if(tileId>3221225470LL) // if the tile was rotated 180º
    { 
        tileId-=3221225472LL;
        angle.first = 180;
    }
    else if(tileId>2684354560LL) //if the tile was rotated 90º
    { 
        tileId-=2684354560LL;
        angle.first = 90;
    }
    else if(tileId>1610612736LL) //if the tile was rotated 90º
    { 
        tileId-=1610612736LL;
        angle.first = 270;
    }
    angle.second = tileId;
    return angle;
}

TileLayer::TileLayer(json* map)
{
    layerWidth = (*map)["width"];
    layerHeight = (*map)["height"];
    layerData = new long long*[layerHeight];
    for (int i = 0; i < layerHeight; i++)
    {
        layerData[i] = new long long[layerWidth];
        for (int j = 0; j < layerWidth; j++)
            layerData[i][j] = static_cast<long long>((*map)["data"][i * layerWidth + j]);

    }
}

TileLayer::~TileLayer()
{
    for (int i = 0; i < layerHeight; i++)
        delete[] layerData[i];
    delete[] layerData;
}

void TileLayer::render(TileSet* tileSet, SDL_Renderer* renderer)
{
    for (int i = 0; i < layerHeight; i++)
    {
        for (int j = 0; j < layerWidth; j++)
        {
            long long id = layerData[i][j];
            if (id != 0)
            {
                pair <int, long long> Reformat_id = Reformat(id);
                Tile* tile = tileSet->tiles[Reformat_id.second];
                tile->render(renderer, i, j, Reformat_id.first);
            }
        }
    }
}
