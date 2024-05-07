#include "SpaceCraft.h"


// Initialize the static member variable
GLuint SpaceCraft::texture;


SpaceCraft::SpaceCraft(GLfloat initialHealth, GLfloat xPos, GLfloat yPos, GLfloat zPos, bool isPlayer) {
    health = initialHealth;
    setPosition(xPos, yPos, zPos);
    player = isPlayer;
}

void SpaceCraft::setHealth(GLfloat newHealth) {
    // Ensure the health value is within the range [0, 100]
    if (newHealth < 0.0f) {
        health = 0.0f;
    } else if (newHealth > 100.0f) {
        health = 100.0f;
    } else {
        health = newHealth;
    }
}

// Setter method for position
void SpaceCraft::setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    position[0] = xPos;
    position[1] = yPos;
    position[2] = zPos;
}

void SpaceCraft::draw() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);

    GLfloat bodyRadius = 1.0;
    GLfloat bodyLength =  2.0;
    GLfloat cockpitRadius = 1.0;
    GLfloat cockpitLength = 0.5;

    // Body of the spacecraft (fuselage)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -bodyLength * 0.5);
    GLUquadric *bodyQuadric = gluNewQuadric();
    gluQuadricTexture(bodyQuadric, GL_TRUE);
    gluCylinder(bodyQuadric, bodyRadius, bodyRadius, bodyLength, 20, 20);
    gluDeleteQuadric(bodyQuadric);
    glPopMatrix();

    // Cap the ends of the cylinder
    glPushMatrix();
    glTranslatef(0.0, 0.0, -bodyLength * 0.5);
    GLUquadric *frontDiskQuadric = gluNewQuadric();
    gluQuadricTexture(frontDiskQuadric, GL_TRUE);
    gluQuadricNormals(frontDiskQuadric, GLU_SMOOTH);
    gluDisk(frontDiskQuadric, 0.0, bodyRadius, 20, 20);
    gluDeleteQuadric(frontDiskQuadric);
    glPopMatrix();

    // Cockpit of the spacecraft
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.5f, 0.5f, 0.8f); // Transparent gray color
    glPushMatrix();
    glTranslatef(0.0, 0.0, bodyLength * 0.5);
    GLUquadric *cockpitQuadric = gluNewQuadric();
    gluQuadricNormals(cockpitQuadric, GLU_SMOOTH);
    gluQuadricTexture(cockpitQuadric, GL_FALSE);
    gluSphere(cockpitQuadric, cockpitRadius, 20, 20);
    gluDeleteQuadric(cockpitQuadric);
    glPopMatrix();
    glDisable(GL_BLEND);

    // Wings of the spacecraft
    GLfloat wingLength = bodyRadius * 2.0;
    GLfloat wingWidth = bodyRadius * 0.4;
    GLfloat wingHeight = bodyRadius * 0.1;

    // Left wing
    glPushMatrix();
    glTranslatef(-bodyRadius * 1.2, 0.0, -bodyLength * 0.25);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-wingLength * 0.5, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(wingLength * 0.5, 0.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(wingLength * 0.5, wingWidth, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-wingLength * 0.5, wingWidth, 0.0);
    glEnd();
    glPopMatrix();

    // Right wing
    glPushMatrix();
    glTranslatef(bodyRadius * 1.2, 0.0, -bodyLength * 0.25);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-wingLength * 0.5, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(wingLength * 0.5, 0.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(wingLength * 0.5, wingWidth, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-wingLength * 0.5, wingWidth, 0.0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
}
