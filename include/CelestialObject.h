#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "IDrawable.h"

class CelestialObject : public IDrawable {
private:
    GLfloat position[3]; // Position of the celestial object

public:
    GLfloat radius; // Radius of the celestial object
    GLuint texture; // Texture of the celestial object

    // Constructor without position
    CelestialObject(GLfloat radius, GLuint texture);

    // Constructor with position
    CelestialObject(GLfloat radius, GLuint texture, GLfloat xPos, GLfloat yPos, GLfloat zPos);

    // Function to draw the celestial object
    virtual void draw() const override;
    virtual void drawMoon();

    // Function to animate the celestial object
    virtual void animate(int i);
    virtual void animateMoon();

    // Setter method for position
    void setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos);
};

#endif
