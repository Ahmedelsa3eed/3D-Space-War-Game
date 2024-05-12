#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "IDrawable.h" // Assuming IDrawable.h contains the interface definition
#include "Point.h"

class Projectile : public IDrawable
{
private:
    GLfloat damage;
    Point source;
    Point direction;
    Point position;
    GLfloat bodyRadius = 0.1;
    GLfloat bodyLength = 0.2;
    GLfloat noseLength = 0.08;
    bool owner;

public:
    // Constructor
    Projectile(GLfloat dmg, bool owner, Point source, Point direction);

    Point getPosition();

    Point getDirection();

    // Setter for position
    void setPosition(Point position);

    // Setter for damage
    void setDamage(GLfloat dmg);

    // Getter for damage
    GLfloat getDamage();

    bool getOwner();

    // Draw function from the IDrawable interface
    virtual void draw() const override;

    // update boundin box
    virtual void updateBB() override;

    bool operator==(const Projectile &other) const;

    struct HashFunction
    {
        size_t operator()(const Projectile &projectile) const;
    };
};

#endif // PROJECTILE_H
