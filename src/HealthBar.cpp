#include "HealthBar.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

// Function to draw the health bar
void HealthBar::draw(float health) {
    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);

    // Switch to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw the health bar at the bottom left corner
    float barWidth = 200.0f; // Adjust the width of the health bar
    float barHeight = 20.0f; // Adjust the height of the health bar
    float padding = 10.0f; // Adjust the padding from the edges of the window
    float xPos = padding;
    float yPos = padding;

    // Calculate the width of the healthy portion of the bar
    float healthyWidth = (health / 100.0f) * (barWidth - 2 * padding);

    // Set the color to green for the healthy portion of the bar
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos); // Top left
    glVertex2f(xPos + healthyWidth, yPos); // Top right
    glVertex2f(xPos + healthyWidth, yPos + barHeight); // Bottom right
    glVertex2f(xPos, yPos + barHeight); // Bottom left
    glEnd();

    // Set the color to red for the damaged portion of the bar
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(xPos + healthyWidth, yPos); // Top left
    glVertex2f(xPos + barWidth, yPos); // Top right
    glVertex2f(xPos + barWidth, yPos + barHeight); // Bottom right
    glVertex2f(xPos + healthyWidth, yPos + barHeight); // Bottom left
    glEnd();

    // Restore modelview matrix
    glPopMatrix();

    // Restore projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0f, 1.0f, 1.0f);
}

void HealthBar::drawEnemyHealthBar(float health) {
    // Set the color to green for the healthy portion of the bar
    glColor3f(0.0f, 1.0f, 0.0f);
    
    // Draw the healthy portion of the bar
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, -0.9f); // Top left
        glVertex2f(-0.9f + (health * 0.018f), -0.9f); // Top right
        glVertex2f(-0.9f + (health * 0.018f), -0.85f); // Bottom right
        glVertex2f(-0.9f, -0.85f); // Bottom left
    glEnd();
    
    // Set the color to red for the damaged portion of the bar
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // Draw the damaged portion of the bar
    glBegin(GL_QUADS);
        glVertex2f(-0.9f + (health * 0.018f), -0.9f); // Top left
        glVertex2f(0.9f, -0.9f); // Top right
        glVertex2f(0.9f, -0.85f); // Bottom right
        glVertex2f(-0.9f + (health * 0.018f), -0.85f); // Bottom left
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
}