#include "CelestialObject.h"
#include <SOIL/SOIL.h>

// Constructor without position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture)
    : radius(radius), texture(texture) {
    setPosition(0.0, 0.0, 0.0); // Default position at the origin
}

// Constructor with position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture, GLfloat xPos, GLfloat yPos, GLfloat zPos)
    : radius(radius), texture(texture) {
    setPosition(xPos, yPos, zPos); // Set the given position
}

// Setter method for position
void CelestialObject::setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    position[0] = xPos;
    position[1] = yPos;
    position[2] = zPos;
}


void CelestialObject::draw() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
