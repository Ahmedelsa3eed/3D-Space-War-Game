#include "Point.h"

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point::Point(const Point &other) : Point(other.x, other.y, other.z) {}

Point Point::operator+(Point const &other)
{
    Point res;
    res.x = this->x + other.x;
    res.y = this->y + other.y;
    res.z = this->z + other.z;
    return res;
}

Point Point::operator-(Point const &other)
{
    Point res;
    res.x = this->x - other.x;
    res.y = this->y - other.y;
    res.z = this->z - other.z;
    return res;
}

Point Point::operator*(const float number)
{
    Point res;
    res.x = number * this->x;
    res.y = number * this->y;
    res.z = number * this->z;
    return res;
}

bool Point::operator==(const Point &other) const
{
    return (this->x == other.x && this->y == other.y && this->z == other.z);
}

size_t Point::HashFunction::operator()(const Point &p) const
{
    size_t hash = std::hash<float>()(p.x);
    hash ^= std::hash<float>()(p.y) << 1;
    hash ^= std::hash<float>()(p.z) << 2;
    return hash;
}
