#pragma once

#include "ECS.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{

    public:
        Vector2D position;
        Vector2D velocity;
        
        int speed = 2;
        float rotationSpeed = 0.0f;
        float rotation = 0.0f;
        TransformComponent() = default;
        TransformComponent(float spon_x, float spon_y)
        {
            position.x = spon_x;
            position.y = spon_y;
        }
        void init () override
        {
            velocity.x = 0;
            velocity.y = 0;
        }
        void update() override
        {
            float angleRad = rotation * M_PI / 180.0f + 180.0f;
            position.x += velocity.x;
            position.y += velocity.y;
            rotation += rotationSpeed;
            if(rotation >= 360.0f)
            {
                rotation = 0;
            }
        }
    
};
