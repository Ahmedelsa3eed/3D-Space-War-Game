#include "Projectile.h"
#include <cmath>

Projectile::Projectile(GLfloat dmg, Point source, Point direction)
{
    this->damage = dmg;
    this->source = source;
    this->direction = direction;
    this->position = source;

    float directionMagnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
    this->direction.x /= directionMagnitude;
    this->direction.y /= directionMagnitude;
    this->direction.z /= directionMagnitude;
}

Point Projectile::getPosition()
{
    return this->position;
}

Point Projectile::getDirection()
{
    return this->direction;
}

void Projectile::setPosition(Point newPosition)
{
    this->position.x = newPosition.x;
    this->position.y = newPosition.y;
    this->position.z = newPosition.z;
}

void Projectile::setDamage(GLfloat dmg)
{
    if (dmg < 0.0f)
    {
        damage = 0.0f;
    }
    else if (dmg > 100.0f)
    {
        damage = 100.0f;
    }
    else
    {
        damage = dmg;
    }
}

GLfloat Projectile::getDamage() const
{
    return damage;
}

void Projectile::draw() const
{

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

bool Projectile::operator==(const Projectile &other) const
{
    return damage == other.damage && source == other.source &&
            direction == other.direction && position == other.position;
}

size_t Projectile::HashFunction::operator()(const Projectile &projectile) const
{
    size_t hash = std::hash<GLfloat>()(projectile.damage);
    hash ^= Point::HashFunction()(projectile.source) << 1;
    hash ^= Point::HashFunction()(projectile.direction) << 2;
    hash ^= Point::HashFunction()(projectile.position) << 3;
    return hash;
}
