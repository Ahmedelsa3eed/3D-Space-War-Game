#include "CelestialObject.h"
#include <SOIL/SOIL.h>

// Constructor without position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture)
    : radius(radius), texture(texture) {
    setPosition(0.0, 0.0, 0.0); // Default position at the origin
    boundingSphere = AABB();
}

// Constructor with position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture, GLfloat xPos, GLfloat yPos, GLfloat zPos)
    : radius(radius), texture(texture) {
    setPosition(xPos, yPos, zPos); // Set the given position
    boundingSphere.update(position, radius);
}

// Setter method for position
void CelestialObject::setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    position.x = xPos;
    position.y = yPos;
    position.z = zPos;
    boundingSphere.update(position, radius);
}

Point CelestialObject::getPosition() {
    return this->position;
}

void CelestialObject::updateBB()  {
    boundingSphere.update(position, radius);
}

void CelestialObject::draw() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
