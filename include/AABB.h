#ifndef AABB_h
#define AABB_h

#include "Point.h"

class AABB
{

private:
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

public:
    AABB();
    

    AABB(Point position, float radius);

    void update(Point position, float radius);

    bool overlaps(const AABB &other);
};

#endif