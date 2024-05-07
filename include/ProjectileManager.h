#pragma once
#include <vector>
#include "IActionManager.h"
#include "Projectile.h"

class ProjectileManager
{
public:
    std::vector<Projectile> projectiles;

    ProjectileManager(float displacementPerTick);
    int addProjectile(Projectile projectile);
    void notifyClockTick();
};
