// IDrawable.h
#ifndef IDrawable_H
#define IDrawable_H

#include <GL/glew.h>
#include <GL/freeglut.h>

// IDrawable interface
class IDrawable {
public:
    virtual void draw() const = 0; // Pure virtual function for drawing
};

#endif // IDrawable_H
