#include "Projectile.h"

Projectile::Projectile(GLfloat dmg, Point source, Point direction) : damage(damage), source(source), direction(direction), position(source) {}

void Projectile::setPosition(Point newPosition) {
    position = newPosition;
}

void Projectile::setDamage(GLfloat dmg) {
    if (dmg < 0.0f) {
        damage = 0.0f;
    } else if (dmg > 100.0f) {
        damage = 100.0f;
    } else {
        damage = dmg;
    }
}

GLfloat Projectile::getDamage() const {
    return damage;
}

void Projectile::draw() const {
    
    GLfloat bodyRadius = 0.1;
    GLfloat bodyLength = 0.2;
    GLfloat noseLength = 0.08;

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the missile
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    // Draw missile body (cylinder)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -bodyLength * 0.5f);
    GLUquadric *bodyQuadric = gluNewQuadric();
    gluQuadricDrawStyle(bodyQuadric, GLU_FILL);
    gluCylinder(bodyQuadric, bodyRadius, bodyRadius, bodyLength, 10, 10);
    gluDeleteQuadric(bodyQuadric);
    glPopMatrix();

    // Draw missile nose (cone)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, bodyLength * 0.5f);
    glRotatef(180, 0.0, 1.0, 0.0);
    GLUquadric *noseQuadric = gluNewQuadric();
    gluQuadricDrawStyle(noseQuadric, GLU_FILL);
    gluCylinder(noseQuadric, 0.0f, bodyRadius, noseLength, 10, 10);
    gluDeleteQuadric(noseQuadric);
    glPopMatrix();

    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
}
