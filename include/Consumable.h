#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "IDrawable.h"
#include <string>

class Consumable : public IDrawable {
private:
    GLfloat position[3]; // Position of the consumable (x, y, z)
    std::string type; // Type of consumable: "health" or "damage"

public:
    Consumable(GLfloat xPos, GLfloat yPos, GLfloat zPos, std::string consumableType);

    // Setter for position
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    
    // Draw function from the IDrawable interface
    virtual void draw() const override;
};

#endif
