#pragma once

#include "ECS.hpp"
#include "../TextureManager.hpp"

class BulletComponent
{
    private:
        SDL_Texture *bulletTexture;
        SDL_Texture *explosionTexture;
        SDL_Rect bulletsrcRect;
        SDL_Renderer *renderer;
        SDL_Rect explosiondestRect;
        SDL_Rect explosionsrcRect;
        Map* map;
        float speed = 10;

    public:
        Vector2D initialPosition; // Position of the gun from which the bullet is
        SDL_Rect bulletdestRect;
        bool isMove;
        float direction;
        

        ~BulletComponent() = default;
        BulletComponent(SDL_Texture *bulletImage,  SDL_Texture *explosionImage, SDL_Renderer *ren, float mSpeed, Map* mapdata)
        {
            bulletTexture = bulletImage;
            renderer = ren;
            speed = mSpeed;
            map = mapdata;
            bulletsrcRect.x = 44;
            bulletsrcRect.y = 46;
            bulletsrcRect.w = 40;
            bulletsrcRect.h = 37;
            bulletdestRect.w = bulletsrcRect.w / SCALEDOWN;
            bulletdestRect.h = bulletsrcRect.h / SCALEDOWN;
            explosionsrcRect.x = 0;
            explosionsrcRect.y = 0;
            explosionsrcRect.w = 256;
            explosionsrcRect.h = 256;
            explosiondestRect.w = explosionsrcRect.w / SCALEDOWN;
            explosiondestRect.h = explosionsrcRect.h / SCALEDOWN;
            isMove = true;

            explosionTexture = explosionImage;
        }

        void CheckBulletCollisionWithWall()
        {
            int finalPositionX = bulletdestRect.x + 1;
            int finalPositionY = bulletdestRect.y + 1;
            bool collide = false;
            for (int i = finalPositionX * SCALEDOWN / map->tileWidth; i <= (finalPositionX + 40/SCALEDOWN -1) * SCALEDOWN / map->tileWidth; ++i)
            {
                for (int j = finalPositionY * SCALEDOWN / map->tileHeight; j <= (finalPositionY + 37/SCALEDOWN -1) * SCALEDOWN / map->tileHeight; ++j)
                {
                    for (auto layer: map->layers)
                    {
                        if (layer->layerType != "tilelayer") continue;
                        int id = layer->tileLayer->getId(j, i);
                        if (map->tileSet->tiles[id]->isCollidable)
                        {
                            collide = true;
                            break;
                        }
                    }
                    if(collide) break;
                }
                if(collide) break;
            }
            if(collide) this->isMove = false;
        }

        void update() 
        {
            CheckBulletCollisionWithWall();
            
            if(isMove)
            {
                bulletdestRect.x += (speed * cos(direction * M_PI / 180.0f));
                bulletdestRect.y += (speed * sin(direction * M_PI / 180.0f));
            }
        }
        void draw()
        {
            if(!isMove)
            {
                explosiondestRect.x = bulletdestRect.x - 64;
                explosiondestRect.y = bulletdestRect.y - 64;
                SDL_RenderCopy(renderer, explosionTexture, &explosionsrcRect, &explosiondestRect);
            }
            else if(isMove)
            {
                SDL_Point BulletCenter = {bulletdestRect.w / 2, bulletdestRect.h / 2}; // Rotation center
                SDL_RenderCopyEx(renderer, bulletTexture, &bulletsrcRect, &bulletdestRect, direction, &BulletCenter, SDL_FLIP_NONE);
            }
        }

        
};
