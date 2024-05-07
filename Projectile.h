#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Drawable.h" // Assuming Drawable.h contains the interface definition

class Projectile : public Drawable {
private:
    GLfloat position[3]; // Position of the projectile (x, y, z)
    GLfloat damage;      // Damage inflicted by the projectile (0 to 100)

public:
    // Constructor
    Projectile(GLfloat x, GLfloat y, GLfloat z, GLfloat dmg);

    // Setter for position
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    // Setter for damage
    void setDamage(GLfloat dmg);

    // Getter for damage
    GLfloat getDamage() const;

    // Draw function from the Drawable interface
    virtual void draw() const override;
};

#endif // PROJECTILE_H
