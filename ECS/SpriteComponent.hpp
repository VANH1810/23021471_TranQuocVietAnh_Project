#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "BulletComponent.hpp"
#include "RocketComponent.hpp"
enum class TypeOfBullet
{
    NORMAL,
    ROCKET,
    GATLING,
    TRIPLE_SHOT,
    FAST,
};

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;

    vector<BulletComponent*> bulletsToDelete;
    vector<RocketComponent*> rocketsToDelete;

    SDL_Texture *bulletTexture;
    SDL_Texture *explosionTexture;

    SDL_Texture *TankTexture;
    SDL_Rect TanksrcRect;

    SDL_Texture *WeaponTexture;
    SDL_Rect WeaponsrcRect, WeapondestRect;

    SDL_Renderer *renderer;

    int speed_frames = 100;
    int currentFrame = 0;
    int animated_frames = 0;

    Mix_Chunk *soundEffect;
    struct PendingBullet {
        TypeOfBullet type;
        float delay;
    };
    queue<PendingBullet> pendingBullets;

    
    
public:
    vector<BulletComponent*> bullets;
    vector<RocketComponent*> rockets;
    bool alive = true;
    bool shooting_animated = false;
    SDL_Rect TankdestRect;
    TypeOfBullet now_type_of_bullet;
    pair<int,int> nearestEnemy;

    SpriteComponent() = default;
    ~SpriteComponent()
    {
        SDL_DestroyTexture(TankTexture);
        SDL_DestroyTexture(WeaponTexture);
        SDL_DestroyTexture(bulletTexture);
        SDL_DestroyTexture(explosionTexture);
        Mix_FreeChunk(soundEffect);
        for(auto bullet : bullets)
            delete bullet;
        for(auto bullet : bulletsToDelete)
            delete bullet;
        while(!pendingBullets.empty())
            pendingBullets.pop();
    }
    SpriteComponent(const string &tank_path, const string &weapon_path, const string &bullet_path, const string &explosion_path, SDL_Renderer *ren, int nFrames, int mSpeed)
    {
        animated_frames = nFrames;
        speed_frames = mSpeed;
        renderer = ren;
        TankTexture = TextureManager::LoadTexture(tank_path.c_str(), ren);
        WeaponTexture = TextureManager::LoadTexture(weapon_path.c_str(), ren);
        bulletTexture = TextureManager::LoadTexture(bullet_path.c_str(), ren);
        explosionTexture = TextureManager::LoadTexture(explosion_path.c_str(), ren);
        soundEffect = AudioManager::LoadSound("assets/TankBulletExplosion.wav");
        now_type_of_bullet = TypeOfBullet::NORMAL;
    }
    

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        TanksrcRect.x = TanksrcRect.y = 27;
        WeaponsrcRect.x = WeaponsrcRect.y = 0;
        TanksrcRect.w = 72;
        TanksrcRect.h = 80;
        WeaponsrcRect.w = 128;
        WeaponsrcRect.h = 128;

        TankdestRect.w = TanksrcRect.w;
        TankdestRect.h = TanksrcRect.h;
        WeapondestRect.w = WeaponsrcRect.w;
        WeapondestRect.h = WeaponsrcRect.h;
    }
    void shoot()
    {
        if(!alive) return;
        if(now_type_of_bullet == TypeOfBullet::NORMAL)
        {
            BulletComponent* newBullet = new BulletComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect, 2.5f);
            newBullet->bulletdestRect.x = transform->position.x;
            newBullet->bulletdestRect.y = transform->position.y;
            newBullet->direction = transform->rotation;
            newBullet->isMove = true;
            bullets.push_back(newBullet); 
        }
        else if(now_type_of_bullet == TypeOfBullet::FAST)
        {
            BulletComponent* newBullet = new BulletComponent(bulletTexture, explosionTexture, renderer, 50.0f, transform->map, soundEffect, 0.8f);
            newBullet->bulletdestRect.x = transform->position.x;
            newBullet->bulletdestRect.y = transform->position.y;
            newBullet->direction = transform->rotation;
            newBullet->isMove = true;
            bullets.push_back(newBullet); 
            now_type_of_bullet = TypeOfBullet::NORMAL;
        }
        else if (now_type_of_bullet == TypeOfBullet::GATLING)
        {
           for (int i = 0; i < 3; ++i) 
           {
                PendingBullet bullet = { TypeOfBullet::GATLING, i * 0.1f };
                pendingBullets.push(bullet);
            }
            now_type_of_bullet = TypeOfBullet::NORMAL;
        }
        else if(now_type_of_bullet == TypeOfBullet::TRIPLE_SHOT)
        {
            BulletComponent* newBullet1 = new BulletComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect, 2.0f);
            newBullet1->bulletdestRect.x = transform->position.x;
            newBullet1->bulletdestRect.y = transform->position.y;
            newBullet1->direction = transform->rotation;
            newBullet1->isMove = true;
            bullets.push_back(newBullet1);

            BulletComponent* newBullet2 = new BulletComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect,2.0f);
            newBullet2->bulletdestRect.x = transform->position.x;
            newBullet2->bulletdestRect.y = transform->position.y;
            newBullet2->direction = transform->rotation + 30.0f;
            newBullet2->isMove = true;
            bullets.push_back(newBullet2);

            BulletComponent* newBullet3 = new BulletComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect,2.0f);
            newBullet3->bulletdestRect.x = transform->position.x;
            newBullet3->bulletdestRect.y = transform->position.y;
            newBullet3->direction = transform->rotation - 30.0f;
            newBullet3->isMove = true;
            bullets.push_back(newBullet3);

        }
        else if(now_type_of_bullet == TypeOfBullet::ROCKET)
        {
            RocketComponent* newRocket = new RocketComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect, 2.0f);
            newRocket->rocketdestRect.x = transform->position.x;
            newRocket->rocketdestRect.y = transform->position.y;
            newRocket->direction = transform->rotation;
            newRocket->isMove = true;
            newRocket->targetX = nearestEnemy.first;
            newRocket->targetY = nearestEnemy.second;

            rockets.push_back(newRocket); 
            now_type_of_bullet = TypeOfBullet::NORMAL;
        }
    }
    void update() override
    {
        if(!alive)
        {
            now_type_of_bullet = TypeOfBullet::NORMAL;

            TankdestRect.x = -1000;
            TankdestRect.y = -1000;
            WeapondestRect.x = -1000;
            WeapondestRect.y = -1000;

            while(!pendingBullets.empty())
                pendingBullets.pop();
            return;
        }
        if (!pendingBullets.empty()) 
        {
            PendingBullet& bullet = pendingBullets.front();
            bullet.delay -= 1.0f / 60.0f;  

            if (bullet.delay <= 0) 
            {
                
                BulletComponent* newBullet = new BulletComponent(bulletTexture, explosionTexture, renderer, 8.0f, transform->map, soundEffect, 2.0f);
                newBullet->bulletdestRect.x = transform->position.x;
                newBullet->bulletdestRect.y = transform->position.y;
                newBullet->direction = transform->rotation;
                newBullet->isMove = true;
                bullets.push_back(newBullet); 

                pendingBullets.pop();
            }
        }

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
        for(RocketComponent* rocket : rockets) 
        {
            if(rocket->isMove) {
                rocket->targetX = nearestEnemy.first;
                rocket->targetY = nearestEnemy.second;
                rocket->update();

            }
            else {
                rocketsToDelete.push_back(rocket);
            }
        }
        TankdestRect.x = (int) transform->position.x;
        TankdestRect.y = (int) transform->position.y;
        WeapondestRect.x = (int) transform->position.x;
        WeapondestRect.y = (int) transform->position.y;
    }

    void draw() override
    {
        if(alive == false) return;
        SDL_Rect TankdestRectCopy = TankdestRect; 
        TankdestRectCopy.x = (int) transform->position.x - TankdestRect.w / 2; 
        TankdestRectCopy.y = (int) transform->position.y - TankdestRect.h / 2;
        SDL_Point Tankcenter = {TankdestRect.w / 2, TankdestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, TankTexture, &TanksrcRect, &TankdestRectCopy, transform->rotation + 90.0f, &Tankcenter, SDL_FLIP_NONE);

        SDL_Rect WeapondestRectCopy = WeapondestRect;
        WeapondestRectCopy.x = (int) transform->position.x - WeapondestRect.w / 2; 
        WeapondestRectCopy.y = (int) transform->position.y - WeapondestRect.w / 2; 
        SDL_Point Weaponcenter = {WeapondestRect.w / 2, WeapondestRect.h / 2}; // Rotation center
        SDL_RenderCopyEx(renderer, WeaponTexture, &WeaponsrcRect, &WeapondestRectCopy, transform->rotation + 90.0f, &Weaponcenter, SDL_FLIP_NONE);
        
        for(BulletComponent* bullet : bullets) 
        { 
            bullet->draw();
        }
        for(BulletComponent* bullet : bulletsToDelete) {
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
            delete bullet;
        }
        bulletsToDelete.clear(); 

        for(RocketComponent* rocket : rockets) 
        { 
            rocket->draw();
        }
        for(RocketComponent* rocket : rocketsToDelete) {
            rockets.erase(std::remove(rockets.begin(), rockets.end(), rocket), rockets.end());
            delete rocket;
        }
        rocketsToDelete.clear();
    }

    
};


