#pragma once

class Point
{
public:
    float x, y, z;

    Point() = default;
    Point(float x, float y, float z);
    Point(const Point &other);
};
