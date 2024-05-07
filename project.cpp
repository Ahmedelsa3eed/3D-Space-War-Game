#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

const unsigned int CLOCK_TICK_PERIOD = 50;

// Global variables for celestial bodies
GLuint sunTexture;
GLuint mercuryTexture, venusTexture, earthTexture, marsTexture;
GLuint jupiterTexture, saturnTexture, uranusTexture, neptuneTexture;
GLuint moonTexture;

// Camera position
GLfloat cameraX = 0.0f;
GLfloat cameraY = 20.0f;
GLfloat cameraZ = 50.0f;
GLfloat cameraYaw = 0.0f; // Yaw angle (rotation around the y-axis)
GLfloat cameraPitch = 0.0f; // Pitch angle (rotation around the x-axis)

// Function to load textures
void loadTextures() {
    sunTexture = SOIL_load_OGL_texture("textures/sun.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    // Load textures for other celestial bodies
    mercuryTexture = SOIL_load_OGL_texture("textures/mercury.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    venusTexture = SOIL_load_OGL_texture("textures/venus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    earthTexture = SOIL_load_OGL_texture("textures/earth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    marsTexture = SOIL_load_OGL_texture("textures/mars.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    jupiterTexture = SOIL_load_OGL_texture("textures/jupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    saturnTexture = SOIL_load_OGL_texture("textures/saturn.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    uranusTexture = SOIL_load_OGL_texture("textures/uranus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    neptuneTexture = SOIL_load_OGL_texture("textures/neptune.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    moonTexture = SOIL_load_OGL_texture("textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

// Function to draw a celestial body
void drawCelestialBody(GLfloat radius, GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, 30, 30);
    gluDeleteQuadric(quadric);
    glDisable(GL_TEXTURE_2D);
}

// Function to draw a spacecraft
void drawSpacecraft(GLfloat bodyRadius, GLfloat bodyLength, GLfloat cockpitRadius, GLfloat cockpitLength) {
    // Body of the spacecraft (fuselage)
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5); // Gray color for the spacecraft body
    glTranslatef(0.0, 0.0, -bodyLength * 0.5);
    glutSolidCylinder(bodyRadius, bodyLength, 20, 20);
    glPopMatrix();

    // Cockpit of the spacecraft
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); // Green color for the spacecraft cockpit
    glTranslatef(0.0, 0.0, bodyLength * 0.5);
    glutSolidSphere(cockpitRadius, 20, 20);
    glPopMatrix();

    // Wings of the spacecraft
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5); // Gray color for the wings
    GLfloat wingLength = bodyRadius * 1.5;
    GLfloat wingWidth = bodyRadius * 0.2;
    // Left wing
    glPushMatrix();
    glTranslatef(-wingLength * 0.5, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidCone(wingLength, wingWidth, 20, 20);
    glPopMatrix();
    // Right wing
    glPushMatrix();
    glTranslatef(wingLength * 0.5, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidCone(wingLength, wingWidth, 20, 20);
    glPopMatrix();
    glPopMatrix();

    // Engines of the spacecraft
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Red color for the engines
    // Left engine
    glPushMatrix();
    glTranslatef(-bodyRadius * 0.8, 0.0, -bodyLength * 0.5);
    glutSolidSphere(bodyRadius * 0.4, 20, 20);
    glPopMatrix();
    // Right engine
    glPushMatrix();
    glTranslatef(bodyRadius * 0.8, 0.0, -bodyLength * 0.5);
    glutSolidSphere(bodyRadius * 0.4, 20, 20);
    glPopMatrix();
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
}

// Drawing routine
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position and orient the camera
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);


    // Draw the Sun
    glPushMatrix();
    drawCelestialBody(5.0, sunTexture); // Radius of Sun: 5.0
    glPopMatrix();

    // Draw the planets
    // Mercury
    glPushMatrix();
    glTranslatef(10.0, 0.0, 0.0); // Distance from Sun: 10.0
    drawCelestialBody(0.5, mercuryTexture); // Radius of Mercury: 0.5
    glPopMatrix();

    // Venus
    glPushMatrix();
    glTranslatef(15.0, 0.0, 0.0); // Distance from Sun: 15.0
    drawCelestialBody(1, venusTexture); // Radius of Venus: 1
    glPopMatrix();

    // Earth
    glPushMatrix();
    glTranslatef(20.0, 0.0, 0.0); // Distance from Sun: 20.0
    drawCelestialBody(1, earthTexture); // Radius of Earth: 1
    glPopMatrix();

    // Mars
    glPushMatrix();
    glTranslatef(25.0, 0.0, 0.0); // Distance from Sun: 25.0
    drawCelestialBody(0.8, marsTexture); // Radius of Mars: 0.8
    glPopMatrix();

    // Jupiter
    glPushMatrix();
    glTranslatef(35.0, 0.0, 0.0); // Distance from Sun: 35.0
    drawCelestialBody(2.5, jupiterTexture); // Radius of Jupiter: 2.5
    glPopMatrix();

    // Saturn
    glPushMatrix();
    glTranslatef(45.0, 0.0, 0.0); // Distance from Sun: 45.0
    drawCelestialBody(2, saturnTexture); // Radius of Saturn: 2
    glPopMatrix();

    // Uranus
    glPushMatrix();
    glTranslatef(55.0, 0.0, 0.0); // Distance from Sun: 55.0
    drawCelestialBody(1.7, uranusTexture); // Radius of Uranus: 1.7
    glPopMatrix();

    // Neptune
    glPushMatrix();
    glTranslatef(65.0, 0.0, 0.0); // Distance from Sun: 65.0
    drawCelestialBody(1.4, neptuneTexture); // Radius of Neptune: 1.4
    glPopMatrix();

    // Draw the moon
    glPushMatrix();
    glTranslatef(22.0, 0.0, 0.0); // Distance from Earth: 17.0
    drawCelestialBody(0.2, moonTexture); // Radius of Moon: 0.2
    glPopMatrix();

    // Draw the spacecraft
    glPushMatrix();
    glTranslatef(15.0, 0.0, 5.0); // Position of the spacecraft
    drawSpacecraft(1.0, 2.0, 1.0, 0.5); // Adjust the parameters as needed
    glPopMatrix();

    glutSwapBuffers();
}

// Initialization routine
void setup(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    loadTextures(); // Load textures for celestial bodies
}

// OpenGL window reshape routine
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10000.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraZ -= 1.0f; // Move forward
        break;
    case 's':
        cameraZ += 1.0f; // Move backward
        break;
    case 'a':
        cameraX -= 1.0f; // Move left
        break;
    case 'd':
        cameraX += 1.0f; // Move right
        break;
    case 'z':
        cameraY -= 1.0f; // Move down
        break;
    case 'x':
        cameraY += 1.0f; // Move up
        break;
    case 27:
        exit(0); // Exit on ESC
        break;
    }
}

// Function to handle mouse input for camera rotation
void mouseMotion(int x, int y) {
    static int lastX = -1;
    static int lastY = -1;

    if (lastX == -1 || lastY == -1) {
        lastX = x;
        lastY = y;
        return;
    }

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    cameraYaw += deltaX * 0.1f;
    cameraPitch += deltaY * 0.1f;

    if (cameraPitch > 90.0f) cameraPitch = 90.0f;
    if (cameraPitch < -90.0f) cameraPitch = -90.0f;

    lastX = x;
    lastY = y;
}

// Timer function.
void clockTick(int value)
{
    glutPostRedisplay();
    glutTimerFunc(CLOCK_TICK_PERIOD, clockTick, value);
}

// Main routine
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutPassiveMotionFunc(mouseMotion);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    clockTick(-1);
    glutMainLoop();
    return 0;
}
