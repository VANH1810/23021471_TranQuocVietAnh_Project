#pragma once

#include "ECS/Components.hpp"
#include "ECS/ECS.hpp"
#include "BulletPackage.hpp"
class HandleCollectBulletPackage
{
private:
    Entity* Player;
    SpriteComponent* sprite;
    vector<BulletPackage*> bulletPackages;
    vector<BulletPackage*> packageToDelete;
public:
    HandleCollectBulletPackage() = default;
    ~HandleCollectBulletPackage() = default;
    HandleCollectBulletPackage(Entity& Player)
    {
        this->Player = &Player;
        if(Player.hasComponent<SpriteComponent>())
        {
            sprite = &(this->Player->getComponent<SpriteComponent>());
        }
        else cerr << "The entity does not have a sprite component" << endl;
    }
    
    void update(vector<BulletPackage*> &Packages)
    {
        for (BulletPackage* package : Packages) 
        {
            
            if (sprite->TankdestRect.x < package->destRect.x + package->destRect.w &&
                sprite->TankdestRect.x + sprite->TankdestRect.w > package->destRect.x &&
                sprite->TankdestRect.y < package->destRect.y + package->destRect.h &&
                sprite->TankdestRect.y + sprite->TankdestRect.h > package->destRect.y)
            {
                if(package->type == "Rocket")
                {
                    sprite->now_type_of_bullet = TypeOfBullet::ROCKET;
                }
                else if(package->type == "Gatling")
                {
                    sprite->now_type_of_bullet = TypeOfBullet::GATLING;
                }
                else if(package->type == "Triple")
                {
                    sprite->now_type_of_bullet = TypeOfBullet::TRIPLE_SHOT;
                }
                else if(package->type == "Fast")
                {
                    sprite->now_type_of_bullet = TypeOfBullet::FAST;
                }
                if (find(packageToDelete.begin(), packageToDelete.end(), package) == packageToDelete.end()) {
                    packageToDelete.push_back(package);
                }
                
            }
        }

        for (BulletPackage* package : packageToDelete) 
        {
            auto it = find(Packages.begin(), Packages.end(), package);
            if (it != Packages.end()) {
                Packages.erase(it);
            }
            delete package;
        }
        packageToDelete.clear();
    } 
};