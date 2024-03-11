#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *TankTexture;
    SDL_Rect TanksrcRect, TankdestRect;
    SDL_Texture *WeaponTexture;
    SDL_Rect WeaponsrcRect, WeapondestRect;
    SDL_Renderer *renderer;
    float spon1, spon2;

public:
    SpriteComponent() = default;
    ~SpriteComponent() = default;
    SpriteComponent(const string &tank_path, const string &weapon_path, SDL_Renderer *ren)
    {
        renderer = ren;
        TankTexture = TextureManager::LoadTexture(tank_path.c_str(), renderer);
        WeaponTexture = TextureManager::LoadTexture(weapon_path.c_str(), renderer);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        TanksrcRect.x = TanksrcRect.y = 0;
        WeaponsrcRect.x = WeaponsrcRect.y = 0;
        TanksrcRect.w = TanksrcRect.h = 128;
        WeaponsrcRect.w = WeaponsrcRect.h = 128;
        TankdestRect.w = TankdestRect.h = 128 / SCALEDOWN;
        WeapondestRect.w = WeapondestRect.h = 128 / SCALEDOWN;
    }
    void update() override
    {
        TankdestRect.x = (int) transform->position.x;
        TankdestRect.y = (int) transform->position.y;
        WeapondestRect.x = (int) transform->position.x;
        WeapondestRect.y = (int) transform->position.y;
    }
    void draw() override
    {
        SDL_Rect TankdestRectCopy = TankdestRect; // Create a copy of destRect
        TankdestRectCopy.x = (int) transform->position.x - TankdestRect.w / 2; // Update the copy
        TankdestRectCopy.y = (int) transform->position.y - TankdestRect.h / 2;
        SDL_Point Tankcenter = {TankdestRect.w / 2, TankdestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, TankTexture, &TanksrcRect, &TankdestRectCopy, transform->rotation + 90.0f, &Tankcenter, SDL_FLIP_NONE);

        SDL_Rect WeapondestRectCopy = WeapondestRect; // Create a copy of destRect
        WeapondestRectCopy.x = (int) transform->position.x - WeapondestRect.w / 2; 
        WeapondestRectCopy.y = (int) transform->position.y - WeapondestRect.w / 2; 
        SDL_Point Weaponcenter = {WeapondestRect.w / 2, WeapondestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, WeaponTexture, &WeaponsrcRect, &WeapondestRectCopy, transform->rotation + 90.0f, &Weaponcenter, SDL_FLIP_NONE);
    }

    
};

