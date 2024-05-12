#pragma once
#include <functional>
#include <ostream>
#include <iostream>
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
    void printPoint() {
        std::cout << x << " " << y << " " << z << std::endl;
    }
    struct HashFunction
    {
        size_t operator()(const Point &p) const;
    };
};
