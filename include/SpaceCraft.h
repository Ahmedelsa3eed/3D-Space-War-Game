#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "IDrawable.h" // Assuming IDrawable.h contains the interface definition
#include "Point.h"
#include "Consumable.h"
#include "ProjectileManager.h"
#include "Projectile.h"

class SpaceCraft : public IDrawable {
private:
    GLfloat health; // Health of the spacecraft (0 to 100)
    Point position; // Position of the spacecraft (x, y, z)
    bool player; // Indicates whether the spacecraft is controlled by the player
    GLfloat damage;

    GLfloat bodyRadius = 1.0;
    GLfloat bodyLength =  2.0;
    GLfloat cockpitRadius = 1.0;
    GLfloat cockpitLength = 0.5;

    GLfloat wingLength = bodyRadius * 2.0;
    GLfloat wingWidth = bodyRadius * 0.4;
    GLfloat wingHeight = bodyRadius * 0.1;

public:

    // Static member variable to store the common texture for all spacecraft objects
    static GLuint texture;

    SpaceCraft() = default;
    SpaceCraft(GLfloat initialHealth, GLfloat dmg, GLfloat xPos, GLfloat yPos, GLfloat zPos, bool isPlayer);

    // Setter for health
    void setHealth(GLfloat newHealth);

    // Getter for health
    GLfloat getHealth();

    // Setter for position
    void setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos);

    // Getter for the position
    Point getPosition();

    // Setter for damage
    void setDamage(GLfloat dmg);

    GLfloat getDamage();

    void useConsumable(Consumable cons);
    void useProjectile(Projectile proj);

    void shoot(ProjectileManager *manager, Projectile *proj);

    // Draw function from the IDrawable interface
    virtual void draw() const override;

    // update boundin box
    virtual void updateBB() override; 
};

#endif
