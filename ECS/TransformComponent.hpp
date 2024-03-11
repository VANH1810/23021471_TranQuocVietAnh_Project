#pragma once

#include "ECS.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{
    public:
        Vector2D position;
        Vector2D velocity;

        int speed = 2;
        float rotationSpeed = 3.0f;
        float rotation = 0.0f;
        TransformComponent()
        {
            position.x = 64.0f;
            position.y = 64.0f;
        }
        TransformComponent(float x, float y)
        {
            position.x = x;
            position.y = y;
        }
        void init () override
        {
            velocity.x = 0;
            velocity.y = 0;
        }
        void update() override
        {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};
