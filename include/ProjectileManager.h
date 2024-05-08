#pragma once
#include <unordered_set>
#include "IActionManager.h"
#include "Projectile.h"

class ProjectileManager
{
public:
    std::unordered_set<Projectile*> projectiles;
    float displacementPerTick;

    ProjectileManager(float displacementPerTick);
    ~ProjectileManager();
    void addProjectile(Projectile *projectile);
    void notifyClockTick();
};
