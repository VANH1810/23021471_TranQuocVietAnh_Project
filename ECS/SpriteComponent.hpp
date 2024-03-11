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
        TextureManager::Draw(renderer, texture, srcRect, destRect);
    }
};