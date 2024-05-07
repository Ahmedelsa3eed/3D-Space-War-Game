#pragma once
#include "IDrawable.h"
#include "Point.h"

class Projectile : public IDrawable
{
public:
    const int damage;
    const Point source;
    const Point direction;
    const Point position;

    Projectile(const int damage, const Point &source, const Point &direction);
    void draw();
};
