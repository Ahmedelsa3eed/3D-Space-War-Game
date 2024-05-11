#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(float displacementPerTick) : displacementPerTick(displacementPerTick) {}

ProjectileManager::~ProjectileManager()
{
    for (Projectile *projectile : this->projectiles)
    {
        delete projectile;
    }
}

void ProjectileManager::addProjectile(Projectile *projectile)
{
    this->projectiles.insert(projectile);
}

#include<iostream>
void ProjectileManager::notifyClockTick()
{
    for (Projectile *projectile : this->projectiles)
    {
        projectile->draw();
        //std::cout << "Before" << std::endl;
        //projectile->getPosition().printPoint();
        projectile->setPosition(projectile->getPosition() + projectile->getDirection() * displacementPerTick);
        //std::cout << "After" << std::endl;

        //projectile->getPosition().printPoint();


    }
}
