#pragma once

#include "../ECS/Components.hpp"
#include "../ECS/ECS.hpp"
#include "BulletPackage.cpp"

class HandleCollectBulletPackage
{
    private:
        Entity* Player;
        SpriteComponent* sprite;
        vector<BulletPackage*> bulletPackages;
        vector<BulletPackage*> packageToDelete;
    public:
        ~HandleCollectBulletPackage();
        HandleCollectBulletPackage(Entity& Player);
        void update(vector<BulletPackage*> &Packages);
};