#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "CelestialObject.h"
#include "SpaceCraft.h"
#include "Projectile.h"
#include "Consumable.h"
#include "Menu.h"

#include <vector>

const unsigned int CLOCK_TICK_PERIOD = 50;

// Global variables
GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture, jupiterTexture, saturnTexture, uranusTexture, neptuneTexture, moonTexture;
GLuint spacecraftTexture;

std::vector<CelestialObject> celestialObjects;
SpaceCraft playerSpacecraft;
std::vector<SpaceCraft> enemySpacecrafts;
std::vector<Projectile> projectiles;
std::vector<Consumable> consumables;

// Camera position
GLfloat cameraX = 0.0f;
GLfloat cameraY = 20.0f;
GLfloat cameraZ = 50.0f;
GLfloat cameraYaw = 0.0f; // Yaw angle (rotation around the y-axis)
GLfloat cameraPitch = 0.0f; // Pitch angle (rotation around the x-axis)

Menu menu;

static bool started = false;

// Function to load textures
void loadTextures() {
    sunTexture = SOIL_load_OGL_texture("textures/sun.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    mercuryTexture = SOIL_load_OGL_texture("textures/mercury.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    venusTexture = SOIL_load_OGL_texture("textures/venus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    earthTexture = SOIL_load_OGL_texture("textures/earth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    marsTexture = SOIL_load_OGL_texture("textures/mars.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    jupiterTexture = SOIL_load_OGL_texture("textures/jupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    saturnTexture = SOIL_load_OGL_texture("textures/saturn.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    uranusTexture = SOIL_load_OGL_texture("textures/uranus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    neptuneTexture = SOIL_load_OGL_texture("textures/neptune.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    moonTexture = SOIL_load_OGL_texture("textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    spacecraftTexture = SOIL_load_OGL_texture("textures/spacecraft.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    SpaceCraft::texture = spacecraftTexture;
}

std::vector<CelestialObject> createCelestialObjects() {
    std::vector<CelestialObject> celestialObjects;
    celestialObjects.emplace_back(5.0, sunTexture, 0.0, 0.0, 0.0);
    celestialObjects.emplace_back(0.5, mercuryTexture, 10.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.0, venusTexture, 15.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.0, earthTexture, 20.0, 0.0, 0.0);
    celestialObjects.emplace_back(0.8, marsTexture, 25.0, 0.0, 0.0);
    celestialObjects.emplace_back(2.5, jupiterTexture, 35.0, 0.0, 0.0);
    celestialObjects.emplace_back(2.0, saturnTexture, 45.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.7, uranusTexture, 55.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.4, neptuneTexture, 65.0, 0.0, 0.0);
    celestialObjects.emplace_back(0.2, moonTexture, 22.0, 0.0, 0.0);

    return celestialObjects;
}

std::vector<SpaceCraft> createEnemySpacecrafts() {
    std::vector<SpaceCraft> enemySpacecrafts;
    enemySpacecrafts.emplace_back(100, 15.0, 0.0, -5.0, false);

    SpaceCraft enemySpacecraft;
    enemySpacecraft.setPosition(15.0, 0.0, -10.0);
    enemySpacecrafts.push_back(enemySpacecraft);

    return enemySpacecrafts;
}

std::vector<Projectile> createProjectiles() {
    std::vector<Projectile> projectiles;
    projectiles.emplace_back(10, Point(20.0, 0.0, 5.0), Point(0, 0, 0));
    projectiles.emplace_back(10, Point(20.0, 1.0, 5.0), Point(0, 0, 0));

    return projectiles;
}

std::vector<Consumable> createConsumables() {
    std::vector<Consumable> consumables;
    consumables.emplace_back(25.0, 0.0, 5.0, "health");
    consumables.emplace_back(30.0, 0.0, 5.0, "damage");

    return consumables;
}

// Drawing routine
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Dispaly Game Options
    if (!started) {
        menu.writeMenuOptions();
    }

    // Position and orient the camera
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);


    // Draw the Celestial Objects
    for (const auto& celestialObject : celestialObjects) {
        celestialObject.draw();
    }

    // Draw the player spacecraft
    playerSpacecraft.draw();

    // Draw the enemy spacecrafts
    for (const auto& enemySpacecraft : enemySpacecrafts) {
        enemySpacecraft.draw();
    }

    // Draw Missles
    for (const auto& projectile : projectiles) {
        projectile.draw();
    }

    // Draw Consumables
    for (const auto& consumable : consumables) {
        consumable.draw();
    }

    glutSwapBuffers();
}


// Initialization routine
void setup(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    loadTextures(); // Load textures for celestial objects
    celestialObjects =  createCelestialObjects();
    playerSpacecraft = SpaceCraft(100, 15.0, 0.0, 5.0, true);
    enemySpacecrafts = createEnemySpacecrafts();
    projectiles = createProjectiles();
    consumables = createConsumables();
}

// OpenGL window reshape routine
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 1.0, 10000.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    // Menu buttons
    case 13: // Start on Enter
        started = true;
        glutPostRedisplay();
        break;
    case 'l':
        menu.toggleLevel();
		glutPostRedisplay();
		break;
	case 'm':
		menu.toggleMode();
		glutPostRedisplay();
		break;
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
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Space Wars");
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
