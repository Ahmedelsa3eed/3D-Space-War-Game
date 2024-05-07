// Drawable.h
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

// Drawable interface
class Drawable {
public:
    virtual void draw() const = 0; // Pure virtual function for drawing
};

#endif // DRAWABLE_H
