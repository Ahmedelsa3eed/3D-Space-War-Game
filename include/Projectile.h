#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "IDrawable.h" // Assuming IDrawable.h contains the interface definition
#include "Point.h"

class Projectile : public IDrawable {
private:
    GLfloat damage;
    Point source;
    Point direction;
    Point position;

public:
    // Constructor
    Projectile(GLfloat dmg, Point source, Point direction);

    // Setter for position
    void setPosition(Point position);

    // Setter for damage
    void setDamage(GLfloat dmg);

    // Getter for damage
    GLfloat getDamage() const;

    // Draw function from the IDrawable interface
    virtual void draw() const override;
};

#endif // PROJECTILE_H
