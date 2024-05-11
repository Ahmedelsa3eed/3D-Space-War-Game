#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "IDrawable.h" // Assuming IDrawable.h contains the interface definition

class SpaceCraft : public IDrawable {
private:
    GLfloat health; // Health of the spacecraft (0 to 100)
    GLfloat position[3]; // Position of the spacecraft (x, y, z)
    bool player; // Indicates whether the spacecraft is controlled by the player

public:

    // Static member variable to store the common texture for all spacecraft objects
    static GLuint texture;

    SpaceCraft() = default;
    SpaceCraft(GLfloat initialHealth, GLfloat xPos, GLfloat yPos, GLfloat zPos, bool isPlayer);

    // Setter for health
    void setHealth(GLfloat newHealth);

    // Setter for position
    void setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos);

    GLfloat getPositionX() const { return position[0]; }
    GLfloat getPositionY() const { return position[1]; }
    GLfloat getPositionZ() const { return position[2]; }
    GLfloat getHealth() const { return health; }

    // Draw function from the IDrawable interface
    virtual void draw() const override;
};

#endif
