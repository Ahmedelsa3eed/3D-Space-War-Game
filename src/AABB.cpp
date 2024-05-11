#include "AABB.h"
#include "Point.h"

AABB::AABB()
{
  minX = 0;
  minY = 0;
  minZ = 0;
  maxX = 0;
  maxY = 0;
  maxZ = 0;
}

AABB::AABB(Point position, float radius)
{
  minX = position.x - radius;
  minY = position.y - radius;
  minZ = position.z - radius;

  maxX = position.x + radius;
  maxY = position.y + radius;
  maxZ = position.z + radius;
}



void AABB::update(Point position, float radius)
{
  minX = position.x - radius;
  minY = position.y - radius;
  minZ = position.z - radius;
  maxX = position.x + radius;
  maxY = position.y + radius;
  maxZ = position.z + radius;
}


bool AABB::overlaps(const AABB &other)
{
  return (minX <= other.maxX &&
          maxX >= other.minX &&
          minY <= other.maxY &&
          maxY >= other.minY &&
          minZ <= other.maxZ &&
          maxZ >= other.minZ);
}
