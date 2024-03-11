#pragma once

#include "ECS.hpp"
#include "../Vector2D.cpp"

class KeyboardController : public Component
{
    private:
        SDL_Event *event;
    public:
        KeyboardController() = default;
        ~KeyboardController() = default;
        KeyboardController(SDL_Event *e)
        {
            this->event = e;
            //cerr << &this->event;
        }
        TransformComponent *transform;
        void init () override
        {
            transform = &entity->getComponent<TransformComponent>();
        }
    
        void update() override
        {
            if(event->type == SDL_KEYDOWN)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.x = cos(transform->rotation * M_PI / 180.0f);
                        transform->velocity.y = sin(transform->rotation * M_PI / 180.0f);
                        cout << "W" << endl;
                        break;
                    case SDLK_a:
                        transform->rotationSpeed = -5.0f;
                        cout << "A" << endl;
                        break;
                    case SDLK_s:
                        transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f);
                        transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f);
                        cout << "S" << endl;
                        break;
                    case SDLK_d:
                        transform->rotationSpeed = 5.0f;
                        cout << "D" << endl;
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
    public:
    KeyboardController2() = default;
    ~KeyboardController2() = default;
    KeyboardController2(SDL_Event *e)
        {
            this->event = e;
            //cerr << &this->event;
        }
    void update() override
        {
            if(event->type == SDL_KEYDOWN)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_UP:
                        transform->velocity.x = cos(transform->rotation * M_PI / 180.0f);
                        transform->velocity.y = sin(transform->rotation * M_PI / 180.0f);
                        cout << "Up" << endl;
                        break;
                    case SDLK_LEFT:
                        transform->rotationSpeed = -5.0f;
                        cout << "Left" << endl;
                        break;
                    case SDLK_DOWN:
                        transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f);
                        transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f);
                        cout << "Down" << endl;
                        break;
                    case SDLK_RIGHT:
                        transform->rotationSpeed = 5.0f;
                        cout << "Right" << endl;
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