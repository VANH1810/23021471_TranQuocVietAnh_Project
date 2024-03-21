#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "BulletComponent.hpp"
class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    vector<BulletComponent*> bullets; // Danh sách các viên đạn
    vector<BulletComponent*> bulletsToDelete;
    SDL_Texture *bulletTexture;
    SDL_Texture *TankTexture;
    SDL_Rect TanksrcRect, TankdestRect;
    SDL_Texture *WeaponTexture;
    SDL_Rect WeaponsrcRect, WeapondestRect;
    SDL_Renderer *renderer;
    int speed_frames = 50;
    int currentFrame = 0;
    int animated_frames = 0;
public:
    bool shooting_animated = false;
    SpriteComponent() = default;
    SpriteComponent(const string &tank_path, const string &weapon_path, const string &bullet_path, SDL_Renderer *ren, int nFrames, int mSpeed)
    {

        animated_frames = nFrames;
        speed_frames = mSpeed;
        renderer = ren;
        TankTexture = TextureManager::LoadTexture(tank_path.c_str(), ren);
        WeaponTexture = TextureManager::LoadTexture(weapon_path.c_str(), ren);
        bulletTexture = TextureManager::LoadTexture(bullet_path.c_str(), ren);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        TanksrcRect.x = TanksrcRect.y = 27;
        WeaponsrcRect.x = WeaponsrcRect.y = 0;
        TanksrcRect.w = 72;
        TanksrcRect.h = 80;
        WeaponsrcRect.w = WeaponsrcRect.h = 128;
        TankdestRect.w = 72 / SCALEDOWN;
        TankdestRect.h = 80 / SCALEDOWN;
        WeapondestRect.w = WeapondestRect.h = 128 / SCALEDOWN;
    }
    void shoot()
    {
            BulletComponent* newBullet = new BulletComponent(bulletTexture, renderer, 10.0f, transform->map);
            newBullet->initialPosition = transform->position;
            newBullet->bulletdestRect.x = transform->position.x;
            newBullet->bulletdestRect.y = transform->position.y;
            newBullet->direction = transform->rotation;
            newBullet->isMove = true;
            bullets.push_back(newBullet); 
    }
    void update() override
    {
        if (shooting_animated)
        {
            int currentFrame =  static_cast<int>((SDL_GetTicks() / speed_frames) % animated_frames);
            WeaponsrcRect.x = currentFrame * WeaponsrcRect.w;
            if(currentFrame == animated_frames - 1)
            {
                shooting_animated = false;
            }
            
        }
        for(BulletComponent* bullet : bullets) 
        {
            if(bullet->isMove) {
                bullet->update();
            }
            else {
                bulletsToDelete.push_back(bullet);
            }
        }
        TankdestRect.x = (int) transform->position.x;
        TankdestRect.y = (int) transform->position.y;
        WeapondestRect.x = (int) transform->position.x;
        WeapondestRect.y = (int) transform->position.y;
    }
    void draw() override
    {
        SDL_Rect TankdestRectCopy = TankdestRect; // Create a copy of destRect
        TankdestRectCopy.x = (int) transform->position.x - TankdestRect.w / 2; // Update the copy
        TankdestRectCopy.y = (int) transform->position.y - TankdestRect.h / 2;
        SDL_Point Tankcenter = {TankdestRect.w / 2, TankdestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, TankTexture, &TanksrcRect, &TankdestRectCopy, transform->rotation + 90.0f, &Tankcenter, SDL_FLIP_NONE);

        SDL_Rect WeapondestRectCopy = WeapondestRect; // Create a copy of destRect
        WeapondestRectCopy.x = (int) transform->position.x - WeapondestRect.w / 2; 
        WeapondestRectCopy.y = (int) transform->position.y - WeapondestRect.w / 2; 
        SDL_Point Weaponcenter = {WeapondestRect.w / 2, WeapondestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, WeaponTexture, &WeaponsrcRect, &WeapondestRectCopy, transform->rotation + 90.0f, &Weaponcenter, SDL_FLIP_NONE);
        for(BulletComponent* bullet : bullets) 
        {
            if(bullet->isMove) {
                bullet->draw();
            }
        }
        for(BulletComponent* bullet : bulletsToDelete) {
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
            delete bullet;
        }
        bulletsToDelete.clear(); // Clear the vector after deleting bullets
        
    }

    
};



