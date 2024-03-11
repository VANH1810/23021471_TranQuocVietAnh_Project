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
                        transform->velocity.y = -1;
                        cout << "W" << endl;
                        break;
                    case SDLK_a:
                        transform->rotationSpeed = -1.0f;
                        cout << "A" << endl;
                        break;
                    case SDLK_s:
                        transform->velocity.y = 1;
                        cout << "S" << endl;
                        break;
                    case SDLK_d:
                        transform->rotationSpeed = 1.0f;
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
                        transform->velocity.y = 0;
                        break;
                    case SDLK_a:
                        transform->rotationSpeed = 0.0f;
                        break;
                    case SDLK_s:
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