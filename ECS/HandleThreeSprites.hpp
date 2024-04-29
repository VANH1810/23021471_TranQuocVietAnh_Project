#pragma once 

#include "ECS.hpp"
#include "Components.hpp"

class HandleThreeSprites
{
    private:
        Entity* Player1;
        Entity* Player2;
        Entity* Player3;
        SpriteComponent* sprite1;
        SpriteComponent* sprite2;
        SpriteComponent* sprite3;
    public:
        HandleThreeSprites() = default;
        ~HandleThreeSprites() = default;
        HandleThreeSprites(Entity& Player1, Entity& Player2, Entity& Player3)
        {
            this->Player1 = &Player1;
            this->Player2 = &Player2;
            this->Player3 = &Player3;
            if(Player1.hasComponent<SpriteComponent>() && Player2.hasComponent<SpriteComponent>() && Player3.hasComponent<SpriteComponent>())
            {
                sprite1 = &(this->Player1->getComponent<SpriteComponent>());
                sprite2 = &(this->Player2->getComponent<SpriteComponent>());
                sprite3 = &(this->Player3->getComponent<SpriteComponent>());
            }
            else cerr << "One of the entities does not have a sprite component" << endl;
        }
        void updateNearestEnemies() 
        {
            vector<SpriteComponent*> sprites = {sprite1, sprite2, sprite3};
            for (SpriteComponent* sprite : sprites) 
            {
                SpriteComponent* nearestEnemy = nullptr;
                float minDistance = numeric_limits<float>::max();

                for (SpriteComponent* otherSprite : sprites) 
                {
                    if (sprite == otherSprite) continue; 

                    float dx = sprite->TankdestRect.x - otherSprite->TankdestRect.x;
                    float dy = sprite->TankdestRect.y - otherSprite->TankdestRect.y;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < minDistance) 
                    {
                        minDistance = distance;
                        nearestEnemy = otherSprite;
                    }
                }

                sprite->nearestEnemy.first = nearestEnemy->TankdestRect.x;
                sprite->nearestEnemy.second = nearestEnemy->TankdestRect.y;
            }
        }
        void update()
        {
            if (sprite1->alive && sprite2->alive && sprite3->alive)
            {
                if (sprite1->TankdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                    sprite1->TankdestRect.x + sprite1->TankdestRect.w > sprite2->TankdestRect.x &&
                    sprite1->TankdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                    sprite1->TankdestRect.y + sprite1->TankdestRect.h > sprite2->TankdestRect.y)
                {
                    sprite1->alive = false;
                    sprite2->alive = false;
                }
                if (sprite1->TankdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    sprite1->TankdestRect.x + sprite1->TankdestRect.w > sprite3->TankdestRect.x &&
                    sprite1->TankdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    sprite1->TankdestRect.y + sprite1->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    sprite1->alive = false;
                    sprite3->alive = false;
                }
                if (sprite2->TankdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    sprite2->TankdestRect.x + sprite2->TankdestRect.w > sprite3->TankdestRect.x &&
                    sprite2->TankdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    sprite2->TankdestRect.y + sprite2->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    sprite2->alive = false;
                    sprite3->alive = false;
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
                if (bullet->bulletdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    bullet->bulletdestRect.x + sprite1->TankdestRect.w > sprite3->TankdestRect.x &&
                    bullet->bulletdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    bullet->bulletdestRect.y + sprite1->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    bullet->isMove = false;
                    sprite3->alive = false;
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
                if (bullet->bulletdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    bullet->bulletdestRect.x + sprite2->TankdestRect.w > sprite3->TankdestRect.x &&
                    bullet->bulletdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    bullet->bulletdestRect.y + sprite2->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    bullet->isMove = false;
                    sprite3->alive = false;
                }
            }
            for(BulletComponent* bullet : sprite3->bullets) 
            {
                if (bullet->bulletdestRect.x < sprite1->TankdestRect.x + sprite1->TankdestRect.w &&
                    bullet->bulletdestRect.x + sprite3->TankdestRect.w > sprite1->TankdestRect.x &&
                    bullet->bulletdestRect.y < sprite1->TankdestRect.y + sprite1->TankdestRect.h &&
                    bullet->bulletdestRect.y + sprite3->TankdestRect.h > sprite1->TankdestRect.y)
                {
                    bullet->isMove = false;
                    sprite1->alive = false;
                }
                if (bullet->bulletdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                    bullet->bulletdestRect.x + sprite3->TankdestRect.w > sprite2->TankdestRect.x &&
                    bullet->bulletdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                    bullet->bulletdestRect.y + sprite3->TankdestRect.h > sprite2->TankdestRect.y)
                {
                    bullet->isMove = false;
                    sprite2->alive = false;
                }
            }

            updateNearestEnemies();

            for(RocketComponent* rocket : sprite1->rockets) 
            {
                if (rocket->rocketdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite1->TankdestRect.w > sprite2->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite1->TankdestRect.h > sprite2->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite2->alive = false;
                }
                if (rocket->rocketdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite1->TankdestRect.w > sprite3->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite1->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite3->alive = false;
                }
            }
            for(RocketComponent* rocket : sprite2->rockets) 
            {
                if (rocket->rocketdestRect.x < sprite1->TankdestRect.x + sprite1->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite2->TankdestRect.w > sprite1->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite1->TankdestRect.y + sprite1->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite2->TankdestRect.h > sprite1->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite1->alive = false;
                }
                if (rocket->rocketdestRect.x < sprite3->TankdestRect.x + sprite3->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite2->TankdestRect.w > sprite3->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite3->TankdestRect.y + sprite3->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite2->TankdestRect.h > sprite3->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite3->alive = false;
                }
            }
            for(RocketComponent* rocket : sprite3->rockets) 
            {
                if (rocket->rocketdestRect.x < sprite1->TankdestRect.x + sprite1->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite3->TankdestRect.w > sprite1->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite1->TankdestRect.y + sprite1->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite3->TankdestRect.h > sprite1->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite1->alive = false;
                }
                if (rocket->rocketdestRect.x < sprite2->TankdestRect.x + sprite2->TankdestRect.w &&
                    rocket->rocketdestRect.x + sprite3->TankdestRect.w > sprite2->TankdestRect.x &&
                    rocket->rocketdestRect.y < sprite2->TankdestRect.y + sprite2->TankdestRect.h &&
                    rocket->rocketdestRect.y + sprite3->TankdestRect.h > sprite2->TankdestRect.y)
                {
                    rocket->isMove = false;
                    sprite2->alive = false;
                }
            }
        }

};