#include "Point.h"

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point::Point(const Point &other) : Point(other.x, other.y, other.z) {}
