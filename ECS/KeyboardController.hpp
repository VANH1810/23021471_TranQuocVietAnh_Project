#pragma once

#include "ECS.hpp"
#include "../Vector2D.cpp"

class KeyboardController : public Component
{
    private:
        SDL_Event *event;
        Uint32 lastRPressTime = 0;
        Uint32 minRPressInterval = 3000;
        // Minimum time between J presses in milliseconds
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;
        KeyboardController() = default;
        ~KeyboardController() = default;
        KeyboardController(SDL_Event *e)
        {
            this->event = e;
        }
        
        
        void init () override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }
    
        void update() override
        {
            Uint32 currentTime;
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if(state[SDL_SCANCODE_W]) {
                    if(state[SDL_SCANCODE_A]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_D]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;

                    transform->velocity.x = cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_S]) {
                    if(state[SDL_SCANCODE_A]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_D]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;
                    transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_A]) {
                    transform->rotationSpeed = -5.0f;
                }
                else if(state[SDL_SCANCODE_D]) {
                    transform->rotationSpeed = 5.0f;
                    
                }
                else {
                    transform->rotationSpeed = 0.0f;
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                }
                if(state[SDL_SCANCODE_R]) {
                    currentTime = SDL_GetTicks();
                    if (currentTime > lastRPressTime + minRPressInterval) 
                    {
                        lastRPressTime = currentTime;
                        sprite->shooting_animated = true;
                        sprite->shoot();
                    }              
                }
            }
        }
           
                
        
};

class KeyboardController2 : public KeyboardController
{
    private:
        SDL_Event *event;
        Uint32 lastCtrlPressTime = 0;
        Uint32 minCtrlPressInterval = 3000;
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
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if(state[SDL_SCANCODE_UP]) {
                    if(state[SDL_SCANCODE_LEFT]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_RIGHT]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;

                    transform->velocity.x = cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_DOWN]) {
                    if(state[SDL_SCANCODE_LEFT]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_RIGHT]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;
                    transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_LEFT]) {
                    transform->rotationSpeed = -5.0f;
                }
                else if(state[SDL_SCANCODE_RIGHT]) {
                    transform->rotationSpeed = 5.0f;
                    
                }
                else {
                    transform->rotationSpeed = 0.0f;
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                }
                if(state[SDL_SCANCODE_RCTRL]) {
                    currentTime = SDL_GetTicks();
                    if (currentTime > lastCtrlPressTime + minCtrlPressInterval) 
                    {
                        lastCtrlPressTime = currentTime;
                        sprite->shooting_animated = true;
                        sprite->shoot();
                    }              
                }
            
            }
    }
};

class KeyboardController3 : public KeyboardController
{
    private:
        SDL_Event *event;
        Uint32 lastYPressTime = 0;
        Uint32 minYPressInterval = 3000;
    public:
    KeyboardController3() = default;
    ~KeyboardController3() = default;
    KeyboardController3(SDL_Event *e)
    {
            this->event = e;
    }
    void update() override
    {
            Uint32 currentTime;
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if(state[SDL_SCANCODE_I]) {
                    if(state[SDL_SCANCODE_J]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_L]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;

                    transform->velocity.x = cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_K]) {
                    if(state[SDL_SCANCODE_J]) transform->rotationSpeed = -5.0f;
                    else if(state[SDL_SCANCODE_L]) transform->rotationSpeed = 5.0f;
                    else transform->rotationSpeed = 0.0f;
                    transform->velocity.x = -cos(transform->rotation * M_PI / 180.0f) * transform->speed;
                    transform->velocity.y = -sin(transform->rotation * M_PI / 180.0f) * transform->speed;
                }
                else if(state[SDL_SCANCODE_J]) {
                    transform->rotationSpeed = -5.0f;
                }
                else if(state[SDL_SCANCODE_L]) {
                    transform->rotationSpeed = 5.0f;
                    
                }
                else {
                    transform->rotationSpeed = 0.0f;
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                }
                if(state[SDL_SCANCODE_Y]) {
                    currentTime = SDL_GetTicks();
                    if (currentTime > lastYPressTime + minYPressInterval) 
                    {
                        lastYPressTime = currentTime;
                        sprite->shooting_animated = true;
                        sprite->shoot();
                    }              
                }
            
            }
    }
};