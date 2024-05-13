#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "IDrawable.h"
#include <string>
#include "Point.h"

class Consumable : public IDrawable {
private:
    Point position; // Position of the consumable (x, y, z)
    std::string type; // Type of consumable: "health" or "damage"
    GLfloat radius = 0.2;

public:
    Consumable(GLfloat xPos, GLfloat yPos, GLfloat zPos, std::string consumableType);

    // Setter for position
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    // Getter for the position
    Point getPosition();

    // Getter for type 
    std::string getType();
    
    // Draw function from the IDrawable interface
    virtual void draw() const override;

    // update boundin box
    virtual void updateBB() override;
};

#endif
