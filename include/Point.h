#pragma once
#include <functional>
#include <ostream>

class Point
{
public:
    float x, y, z;

    Point() = default;
    Point(float x, float y, float z);
    Point(const Point &other);
    Point operator+(Point const &other);
    Point operator-(Point const &other);
    Point operator*(const float number);
    bool operator==(const Point &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }
    struct HashFunction
    {
        size_t operator()(const Point &p) const;
    };
};
