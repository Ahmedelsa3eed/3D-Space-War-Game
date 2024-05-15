#include "CelestialObject.h"
#include <SOIL/SOIL.h>
#include "globals.h"

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

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);

    glDisable(GL_TEXTURE_2D);
}

void CelestialObject::animate(int i) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glTranslatef(-10*(i), 0.0, 0.0);
    glRotatef(latAngle*(9-i), 0.0, 1.0, 0.0); //
    glTranslatef(10*(i), 0.0, 0.0);

    if (i) glRotatef(longAngle, 0.0, 1.0, 0.0); // not the sun

    draw();
    // Aniamte a Moon for earth
    if (i==3) animateMoon();
    glPopMatrix();
}

void CelestialObject::drawMoon(){
    glEnable(GL_TEXTURE_2D);
    GLuint moonTexture = SOIL_load_OGL_texture("textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, moonTexture);

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    float moonRadius = 0.2;
    gluSphere(quadric, moonRadius, 30, 30);
    gluDeleteQuadric(quadric);
    glDeleteTextures(1, &moonTexture);

    glDisable(GL_TEXTURE_2D);
}

void CelestialObject::animateMoon() {
    glPushMatrix();
    float xRelativeEarth = 3.0;
    float yRelativeEarth = 0.0;
    float zRelativeEarth = 0.0;
    glRotatef(45, 0.0, 0.0, 1.0);
    glRotatef(latAngle*12, 0.0, 1.0, 0.0);
    glTranslatef(xRelativeEarth, yRelativeEarth, zRelativeEarth);
    drawMoon();
    glPopMatrix();
}
