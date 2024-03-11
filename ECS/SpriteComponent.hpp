#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;

public:
    SpriteComponent() = default;
    ~SpriteComponent() = default;
    SpriteComponent(const string &path, SDL_Renderer *ren)
    {
        renderer = ren;
        texture = TextureManager::LoadTexture(path.c_str(), renderer);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 128;
        destRect.w = destRect.h = 128 / SCALEDOWN;
    }
    void update() override
    {
        destRect.x = (int) transform->position.x;
        destRect.y = (int) transform->position.y;
    }
    void draw() override
    {
        SDL_Rect destRectCopy = destRect; // Create a copy of destRect
        destRectCopy.x = (int) transform->position.x - destRect.w / 2; // Update the copy
        destRectCopy.y = (int) transform->position.y - destRect.h / 2;
        SDL_Point center = {destRect.w / 2, destRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, texture, &srcRect, &destRectCopy, transform->rotation + 90.0f, &center, SDL_FLIP_NONE);
    }
    
};