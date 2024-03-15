#pragma once

#include "ECS.hpp"
#include "../Vector2D.cpp"

class KeyboardController : public Component
{
    private:
        SDL_Event *event;
        Uint32 lastJPressTime = 0;
        Uint32 minJPressInterval = 1000; // Minimum time between J presses in milliseconds
    public:
        KeyboardController() = default;
        ~KeyboardController() = default;
        KeyboardController(SDL_Event *e)
        {
            this->event = e;
        }
        TransformComponent *transform;
        SpriteComponent *sprite;
        void init () override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }
    
        void update() override
        {
            Uint32 currentTime;
            if(event->type == SDL_KEYDOWN)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.x = cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                        transform->velocity.y = sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                        //cout << "W" << endl;
                        break;
                    case SDLK_a:
                        transform->rotationSpeed = -5.0f;
                        //cout << "A" << endl;
                        break;
                    case SDLK_s:
                        transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                        transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                        //cout << "S" << endl;
                        break;
                    case SDLK_d:
                        transform->rotationSpeed = 5.0f;
                        //cout << "D" << endl;
                        break;
                    case SDLK_j:
                        currentTime = SDL_GetTicks();
                        if (currentTime > lastJPressTime + minJPressInterval) {
                            lastJPressTime = currentTime;
                            sprite->shooting_animated = true;
                        }              
                        break;
                    default:
                        break;
                }
            }
            if(event->type == SDL_KEYUP)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.x = 0;
                        transform->velocity.y = 0;
                        break;
                    case SDLK_a:
                        transform->rotationSpeed = 0.0f;
                        break;
                    case SDLK_s:
                        transform->velocity.x = 0;
                        transform->velocity.y = 0;
                        break;
                    case SDLK_d:
                        transform->rotationSpeed = 0.0f;
                        break;
                    default:
                        break;
                }
            
            }
        }
};

class KeyboardController2 : public KeyboardController
{
    private:
        SDL_Event *event;
        Uint32 last1PressTime = 0;
        Uint32 min1PressInterval = 1000;
    public:
    KeyboardController2() = default;
    ~KeyboardController2() = default;
    KeyboardController2(SDL_Event *e)
        {
            this->event = e;
        }
    void update() override
        {
            Uint32 currentTime;
            if(event->type == SDL_KEYDOWN)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_UP:
                        transform->velocity.x = cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                        transform->velocity.y = sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                        //cout << "Up" << endl;
                        break;
                    case SDLK_LEFT:
                        transform->rotationSpeed = -5.0f;
                        //cout << "Left" << endl;
                        break;
                    case SDLK_DOWN:
                        transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                        transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                        //cout << "Down" << endl;
                        break;
                    case SDLK_RIGHT:
                        transform->rotationSpeed = 5.0f;
                        //cout << "Right" << endl;
                        break;
                    case SDLK_1:
                        currentTime = SDL_GetTicks();
                        if (currentTime > last1PressTime + min1PressInterval) {
                            last1PressTime = currentTime;
                            sprite->shooting_animated = true;
                        }              
                        break;
                    default:
                        break;
                }
            }
            if(event->type == SDL_KEYUP)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_UP:
                        transform->velocity.x = 0;
                        transform->velocity.y = 0;
                        break;
                    case SDLK_LEFT:
                        transform->rotationSpeed = 0.0f;
                        break;
                    case SDLK_DOWN:
                        transform->velocity.x = 0;
                        transform->velocity.y = 0;
                        break;
                    case SDLK_RIGHT:
                        transform->rotationSpeed = 0.0f;
                        break;
                    default:
                        break;
                }
            
            }
        }
};