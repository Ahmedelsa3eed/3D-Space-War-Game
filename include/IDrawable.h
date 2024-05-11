// IDrawable.h
#ifndef IDrawable_H
#define IDrawable_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "AABB.h"

// IDrawable interface
class IDrawable {


public:

    AABB boundingSphere;

    virtual void draw() const = 0; // Pure virtual function for drawing
    virtual void updateBB() = 0;

    
    
    bool overlaps(AABB &other) {
        return boundingSphere.overlaps(other);
    }

    
};

#endif // IDrawable_H
