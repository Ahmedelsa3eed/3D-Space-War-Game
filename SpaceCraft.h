#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "Drawable.h" // Assuming Drawable.h contains the interface definition

class SpaceCraft : public Drawable {
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

    // Draw function from the Drawable interface
    virtual void draw() const override;
};

#endif
