#pragma once

#include "Components.hpp"
#include "ECS.hpp"

class HandleBulletsBetweenTwoSprites
{
private:
    Entity* Player1;
    Entity* Player2;
    SpriteComponent* sprite1;
    SpriteComponent* sprite2;
public:
    HandleBulletsBetweenTwoSprites() = default;
    ~HandleBulletsBetweenTwoSprites() = default;
    HandleBulletsBetweenTwoSprites(Entity& Player1, Entity& Player2)
    {
        this->Player1 = &Player1;
        this->Player2 = &Player2;
        if(Player1.hasComponent<SpriteComponent>() && Player2.hasComponent<SpriteComponent>())
        {
            sprite1 = &(this->Player1->getComponent<SpriteComponent>());
            sprite2 = &(this->Player2->getComponent<SpriteComponent>());
        }
        else cout << "One of the entities does not have a sprite component" << endl;
    }
    void update()
    {
        if (sprite1->alive && sprite2->alive)
        {
            if (sprite1->TankdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                sprite1->TankdestRect.x + sprite1->TankdestRect.w > sprite2->TankdestRect.x &&
                sprite1->TankdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                sprite1->TankdestRect.y + sprite1->TankdestRect.h > sprite2->TankdestRect.y)
            {
                sprite1->alive = false;
                sprite2->alive = false;
            }
        }

        for(BulletComponent* bullet : sprite1->bullets) 
        {
            if (bullet->bulletdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                bullet->bulletdestRect.x + sprite1->TankdestRect.w > sprite2->TankdestRect.x &&
                bullet->bulletdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                bullet->bulletdestRect.y + sprite1->TankdestRect.h > sprite2->TankdestRect.y)
            {
                bullet->isMove = false;
                sprite2->alive = false;
            }
            
        }
        for(BulletComponent* bullet : sprite2->bullets) 
        {
            if (bullet->bulletdestRect.x < sprite1->TankdestRect.x + sprite1->TankdestRect.w &&
                bullet->bulletdestRect.x + sprite2->TankdestRect.w > sprite1->TankdestRect.x &&
                bullet->bulletdestRect.y < sprite1->TankdestRect.y + sprite1->TankdestRect.h &&
                bullet->bulletdestRect.y + sprite2->TankdestRect.h > sprite1->TankdestRect.y)
            {
                bullet->isMove = false;
                sprite1->alive = false;

            }
        
        }
    }
};