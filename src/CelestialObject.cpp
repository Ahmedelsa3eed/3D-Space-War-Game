#include "CelestialObject.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp> // Include this header for value_ptr
#include "globals.h"

// Constructor without position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture)
    : radius(radius), texture(texture) {
    setPosition(0.0, 0.0, 0.0); // Default position at the origin
    boundingSphere = AABB();
}

// Constructor with position
CelestialObject::CelestialObject(GLfloat radius, GLuint texture, GLfloat xPos, GLfloat yPos, GLfloat zPos)
    : radius(radius), texture(texture) {
    initialPosition.x = xPos;
    initialPosition.y = yPos;
    initialPosition.z = zPos;
    setPosition(xPos, yPos, zPos); // Set the given position
    boundingSphere.update(position, radius);
}

// Setter method for position
void CelestialObject::setPosition(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    position.x = xPos;
    position.y = yPos;
    position.z = zPos;
    boundingSphere.update(position, radius);
}

Point CelestialObject::getPosition() {
    return this->position;
}

void CelestialObject::updateBB()  {
    boundingSphere.update(position, radius);
}

void CelestialObject::draw() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);

    glDisable(GL_TEXTURE_2D);
}

void CelestialObject::animate(int i) {
    glPushMatrix();
    glTranslatef(initialPosition.x, initialPosition.y, initialPosition.z);
    // if (i==3){
    //     printf("%f, %f, %f  ", position.x, position.y, position.z);
    // }

    glTranslatef(-10*(i), 0.0, 0.0);
    glRotatef(latAngle*(9-i), 0.0, 1.0, 0.0); //
    glTranslatef(10*(i), 0.0, 0.0);

    if (i){ // not the sun
        glRotatef(longAngle, 0.0, 1.0, 0.0);
        // Calculate the new position after transformations
        GLfloat viewMatrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

        // // Convert the current matrix to a glm::mat4
        // glm::mat4 glmMatrix(viewMatrix[0], viewMatrix[1], viewMatrix[2], viewMatrix[3],
        //             viewMatrix[4], viewMatrix[5], viewMatrix[6], viewMatrix[7],
        //             viewMatrix[8], viewMatrix[9], viewMatrix[10], viewMatrix[11],
        //             viewMatrix[12], viewMatrix[13], viewMatrix[14], viewMatrix[15]);


        // // Compute the inverse of the matrix
        // glm::mat4 inverseMatrix = glm::inverse(glmMatrix);

        // // Convert the inverse matrix back to a GLfloat array
        // GLfloat inverseMatrixArray[16];
        // memcpy(inverseMatrixArray, glm::value_ptr(inverseMatrix), sizeof(inverseMatrixArray));

        // Previous position vector
        GLfloat prevPosition[4] = {initialPosition.x, initialPosition.y, initialPosition.z, 1.0};

        // Calculate the new position
        GLfloat newX = viewMatrix[0] * prevPosition[0] + viewMatrix[4] * prevPosition[1] + viewMatrix[8] * prevPosition[2] + viewMatrix[12] * prevPosition[3];
        GLfloat newY = viewMatrix[1] * prevPosition[0] + viewMatrix[5] * prevPosition[1] + viewMatrix[9] * prevPosition[2] + viewMatrix[13] * prevPosition[3];
        GLfloat newZ = viewMatrix[2] * prevPosition[0] + viewMatrix[6] * prevPosition[1] + viewMatrix[10] * prevPosition[2] + viewMatrix[14] * prevPosition[3];

        // Store the new position
        position.x = newX;
        position.y = newY;
        position.z = newZ;
        
    } 

    draw();
    // Aniamte a Moon for earth
    if (i==3) animateMoon();
    glPopMatrix();
}

void CelestialObject::drawMoon(){
    glEnable(GL_TEXTURE_2D);
    GLuint moonTexture = SOIL_load_OGL_texture("textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, moonTexture);

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    float moonRadius = 0.2;
    gluSphere(quadric, moonRadius, 30, 30);
    gluDeleteQuadric(quadric);
    glDeleteTextures(1, &moonTexture);

    glDisable(GL_TEXTURE_2D);
}

void CelestialObject::animateMoon() {
    glPushMatrix();
    float xRelativeEarth = 3.0;
    float yRelativeEarth = 0.0;
    float zRelativeEarth = 0.0;
    glRotatef(45, 0.0, 0.0, 1.0);
    glRotatef(latAngle*12, 0.0, 1.0, 0.0);
    glTranslatef(xRelativeEarth, yRelativeEarth, zRelativeEarth);
    drawMoon();
    glPopMatrix();
}
