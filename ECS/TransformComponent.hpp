#pragma once

#include "ECS.hpp"
#include "../Vector2D.hpp"
class TransformComponent : public Component
{
    public:
        Vector2D position;
        Vector2D velocity;
        Map* map;
        int speed = 3.0f;
        float rotationSpeed = 0.0f;
        float rotation = 0.0f;

        TransformComponent() = default;
        ~TransformComponent() = default;
        TransformComponent(float spon_x, float spon_y, Map* mapdata)
        {
            position.x = spon_x;
            position.y = spon_y;
            map = mapdata;
        }

        void init () override
        {
            velocity.x = 0;
            velocity.y = 0;
        }

        void update() override
        {
            int finalPositionX = position.x + velocity.x - (72)/2 + 1;
            int finalPositionY = position.y + velocity.y - (80)/2 + 1;
            bool collide = false;
            for (int i = finalPositionX * SCALEDOWN / map->tileWidth; i <= (finalPositionX + 72/SCALEDOWN -1) * SCALEDOWN / map->tileWidth; ++i)
            {
                for (int j = finalPositionY * SCALEDOWN / map->tileHeight; j <= (finalPositionY + 80/SCALEDOWN -1) * SCALEDOWN / map->tileHeight; ++j)
                {
                    for (auto layer: map->layers)
                    {
                        if (layer->layerType != "tilelayer") continue;
                        int id = layer->tileLayer->getId(j, i);
                        if (map->tileSet->tiles[id]->isCollidable)
                        {
                            collide = true;
                            return;
                        }
                    }
                }
            }
        
            if (!collide)
            {
                position.x += velocity.x;
                position.y += velocity.y;
            }

            rotation += rotationSpeed;
            if(rotation == 360.0f)
            {
                rotation = 0;
            }
        }
    
};
