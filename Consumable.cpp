#include "Consumable.h"
#include <GL/freeglut.h>

Consumable::Consumable(GLfloat xPos, GLfloat yPos, GLfloat zPos, std::string consumableType) {
    position[0] = xPos;
    position[1] = yPos;
    position[2] = zPos;
    type = consumableType;
}

// Setter method for position
void Consumable::setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    position[0] = xPos;
    position[1] = yPos;
    position[2] = zPos;
}

// Draw function for Consumable
void Consumable::draw() const {
    GLfloat radius = 0.2;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);

    // Disable depth test temporarily
    glDisable(GL_DEPTH_TEST);

    if (type == "health") {
        glColor4f(0.0f, 1.0f, 0.0f, 0.5f); // Green color with 50% transparency for the health sphere
        glutSolidSphere(radius, 20, 20);

        // Draw a plus sign inside the sphere
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // White color for the plus sign with full opacity
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f); // Position the plus sign at the center
        glBegin(GL_QUADS);
        glVertex3f(-radius * 0.1f, radius * 0.3f, 0.0f); // Top-left
        glVertex3f(radius * 0.1f, radius * 0.3f, 0.0f);  // Top-right
        glVertex3f(radius * 0.1f, -radius * 0.3f, 0.0f); // Bottom-right
        glVertex3f(-radius * 0.1f, -radius * 0.3f, 0.0f); // Bottom-left
        glEnd();
        glBegin(GL_QUADS);
        glVertex3f(-radius * 0.3f, radius * 0.1f, 0.0f); // Top-left
        glVertex3f(radius * 0.3f, radius * 0.1f, 0.0f);  // Top-right
        glVertex3f(radius * 0.3f, -radius * 0.1f, 0.0f); // Bottom-right
        glVertex3f(-radius * 0.3f, -radius * 0.1f, 0.0f); // Bottom-left
        glEnd();
        glPopMatrix();
    } else if (type == "damage") {
        glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Red color with 50% transparency for the damage sphere
        glutSolidSphere(radius, 20, 20);

        // Draw an upward-pointing orange triangle inside the damage sphere
        glColor4f(1.0f, 0.5f, 0.0f, 1.0f); // Orange color for the triangle with full opacity
        glBegin(GL_TRIANGLES);
        glVertex3f(-radius * 0.5f, 0.0f, 0.0f); // Left point of the triangle
        glVertex3f(radius * 0.5f, 0.0f, 0.0f);  // Right point of the triangle
        glVertex3f(0.0f, radius * 0.5f, 0.0f);  // Top point of the triangle
        glEnd();
    }

    // Enable depth test back
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);

}
