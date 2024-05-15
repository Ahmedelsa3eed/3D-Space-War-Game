#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "CelestialObject.h"
#include "SpaceCraft.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Consumable.h"
#include "Menu.h"
#include "globals.h"
#include "HealthBar.h"

#include <vector>
#include <glm/glm.hpp>
#include <random>

const unsigned int CLOCK_TICK_PERIOD = 30;

// Global variables
GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture, jupiterTexture, saturnTexture, uranusTexture, neptuneTexture, moonTexture;
GLuint spacecraftTexture;
static int width, height; // Size of the OpenGL window.
float latAngle = 0;   // Definition
float longAngle = 0;  // Definition
bool gameOver = false;
bool winner = false;
std::string isWinner[] = {"Lose", "Win"};

std::vector<CelestialObject> celestialObjects;
SpaceCraft playerSpacecraft;
std::vector<SpaceCraft> enemySpacecrafts;
std::vector<Consumable> consumables;

ProjectileManager projectileManager(0.25);

// Camera position
GLfloat cameraX = 0.0f;
GLfloat cameraY = 20.0f;
GLfloat cameraZ = 50.0f;
GLfloat cameraYaw = 0.0f;   // Yaw angle (rotation around the y-axis)
GLfloat cameraPitch = 0.0f; // Pitch angle (rotation around the x-axis)

Menu menu;
HealthBar healthBar;

static bool started = false;
static bool gameOver = false;

// Function to load textures
void loadTextures()
{
    sunTexture = SOIL_load_OGL_texture("textures/sun.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    mercuryTexture = SOIL_load_OGL_texture("textures/mercury.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    venusTexture = SOIL_load_OGL_texture("textures/venus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    earthTexture = SOIL_load_OGL_texture("textures/earth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    marsTexture = SOIL_load_OGL_texture("textures/mars.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    jupiterTexture = SOIL_load_OGL_texture("textures/jupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    saturnTexture = SOIL_load_OGL_texture("textures/saturn.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    uranusTexture = SOIL_load_OGL_texture("textures/uranus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    neptuneTexture = SOIL_load_OGL_texture("textures/neptune.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    spacecraftTexture = SOIL_load_OGL_texture("textures/spacecraft.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    SpaceCraft::texture = spacecraftTexture;
}

std::vector<CelestialObject> createCelestialObjects()
{
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
    return celestialObjects;
}

std::vector<SpaceCraft> createEnemySpacecrafts()
{
    std::vector<SpaceCraft> enemySpacecrafts;
    enemySpacecrafts.emplace_back(100, 10.0, 15.0, 0.0, -5.0, false);
    return enemySpacecrafts;
}

std::vector<Consumable> createConsumables()
{
    std::vector<Consumable> consumables;
    consumables.emplace_back(25.0, 0.0, 5.0, "health");
    consumables.emplace_back(30.0, 0.0, 5.0, "damage");
    return consumables;
}
Point generate_nearby_point(const Point& point, double factor = 5.0) {
  
  std::mt19937 gen(time(0));
  std::uniform_real_distribution<> dis(-factor, factor);

  double offsetX = dis(gen);
  double offsetY = dis(gen);
  double offsetZ = dis(gen);

  return Point(point.x + offsetX, point.y + offsetY, point.z + offsetZ);
}
void enemySpaceCraftShooting() {
    for (SpaceCraft enemySpacecraft: enemySpacecrafts) {

        Point source = enemySpacecraft.getPosition();
        Point dis;
        if(menu.getLevel() == menu.EASY)
            dis = generate_nearby_point(playerSpacecraft.getPosition(), 10);
        else 
            dis = generate_nearby_point(playerSpacecraft.getPosition(), 5);
        Projectile *proj = new Projectile(10, false, source, dis - source);
        enemySpacecraft.shoot(&projectileManager, proj);
    }
}

void drawObjects()
{

    // Animate the Celestial Objects
    for (int i = 0; i < celestialObjects.size(); ++i)
    {
        celestialObjects[i].animate(i);
    }

    // Draw the player spacecraft
    playerSpacecraft.draw();

    // Draw the enemy spacecrafts
    for (const auto &enemySpacecraft : enemySpacecrafts)
    {
        enemySpacecraft.draw();
    }

    // Draw Consumables
    for (const auto &consumable : consumables)
    {
        consumable.draw();
    }

    
}

void endGame() {
    if(gameOver) return;
    bool endTime;
    static double lastTime = 0.0;  
    double currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    if (currentTime - lastTime >= 60 && menu.getMode() == menu.TIME_ATTACK) {
        lastTime = currentTime;
        endTime = true;
    } 
    else {
        endTime = false;
    }
    if (playerSpacecraft.getHealth() == 0 || (endTime && enemySpacecrafts.size() != 0)) {
        gameOver = true;
        winner = false;
    } 
    if (enemySpacecrafts.size() == 0) {
        gameOver = true;
        winner = true;
    }

    if (gameOver) std::cout << "Game Over You " << isWinner[winner] << std::endl;
}

void drawViewPortBorder()
{
    // Draw a horizontal and vertical line on the left of the viewport to separate the two viewports
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    // horizontal line
    glBegin(GL_LINES);
    glVertex3f(-5.5, 2.85, -5.0);
    glVertex3f(10.0, 2.85, -5.0);
    glEnd();

    // horizontal line
    glBegin(GL_LINES);
    glVertex3f(-5.5, -2.85, -5.0);
    glVertex3f(10.0, -2.85, -5.0);
    glEnd();

    // vertical line
    glBegin(GL_LINES);
    glVertex3f(-5.5, -5.0, -5.0);
    glVertex3f(-5.5, 5.0, -5.0);
    glEnd();
    glLineWidth(1.0);

    // vertical line
    glBegin(GL_LINES);
    glVertex3f(5.5, -5.0, -5.0);
    glVertex3f(5.5, 5.0, -5.0);
    glEnd();
    glLineWidth(1.0);
}

void detectProjectileCollision() {
    for (Projectile *projectile : projectileManager.projectiles) {
        if (playerSpacecraft.boundingSphere.overlaps(projectile->boundingSphere) && !projectile->getOwner()) {
            playerSpacecraft.useProjectile(*projectile);
            projectileManager.projectiles.erase(projectile);
            free(projectile);
            continue;
        }

        for (auto it = enemySpacecrafts.begin(); it != enemySpacecrafts.end();) {
            it->updateBB();
            bool coll = it->overlaps(projectile->boundingSphere);
            if (coll && projectile->getOwner()) {
                it->useProjectile(*projectile);
                projectileManager.projectiles.erase(projectile);
                free(projectile);
                if(it->getHealth() == 0){
                    it = enemySpacecrafts.erase(it);
                }
                break;
            }    
            else {
                it++;
            }
        }
    }
}

// Drawing routine
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gameOver)
    {
        menu.writeGameOver(-0.2, 0.0, -2.0);
        glutSwapBuffers();
        return;
    }

    // Dispaly Game Options
    if (!started)
    {
        cameraY = 20.0f;
        cameraX = 0.0f;
        cameraZ = 50.0f;
        cameraYaw = 0.0f;
        cameraPitch = 0.0f;
        menu.writeMenuOptions();
        glutSwapBuffers();
        return;
    }

    // Begin Main viewport. 
    glViewport(0, 0, width, height);
    glLoadIdentity();

    // Position and orient the camera
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);

    // Draw the player health bar
    healthBar.drawPlayerHealthBar(playerSpacecraft.getHealth());

    // Draw objects in the main viewport
    detectProjectileCollision();
    projectileManager.notifyClockTick();
    drawObjects();

    // ======================================================================================
    // Begin Bottom Right viewport.

    // Enable scissor testing
    glEnable(GL_SCISSOR_TEST);
    glScissor(width - 260, 20, 240, 180);

    // Clear the scissor region to allow drawing in the remaining area
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(width - 260, 20, 240, 180);
    glLoadIdentity();

    drawViewPortBorder();

    // Fixed camera.
    gluLookAt(0.0, 10.0, 120.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw objects again inside the other viewport
    projectileManager.notifyClockTick();
    drawObjects();

    // Disable scissor testing to allow drawing in the remaining area of the screen
    glDisable(GL_SCISSOR_TEST);

    glutSwapBuffers();
}

// Initialization routine
void setup(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    loadTextures(); // Load textures for celestial objects
    celestialObjects =  createCelestialObjects();
    playerSpacecraft = SpaceCraft(100, 10, 15.0, 5.0, 5.0, true);
    enemySpacecrafts = createEnemySpacecrafts();
    consumables = createConsumables();
}

// OpenGL window reshape routine
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 1.0, 10000.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);

    // Pass the size of the OpenGL window.
    width = w;
    height = h;
}


std::pair<bool, SpaceCraft> detectCollision(SpaceCraft plSpace) {
    
    AABB player = plSpace.boundingSphere;
    bool coll = false;

    for (auto& celestialObject : celestialObjects) {                
        coll = celestialObject.overlaps(player);
        if(coll){
            std::cout << "Collision with cele " << std::endl;
            return {true, plSpace};
        }
    }

    for (auto& enemySpacecraft : enemySpacecrafts) {
        enemySpacecraft.updateBB();
        coll = enemySpacecraft.overlaps(player);
        if(coll){
            std::cout << "Collision with enemy " << std::endl;
            return {true, plSpace};
        }
    }

    for (Projectile *projectile : projectileManager.projectiles)
    {        
        projectile->updateBB();
        coll = projectile->overlaps(player);
        if(coll){
            plSpace.useProjectile(*projectile);
            projectileManager.projectiles.erase(projectile);
            free(projectile);
            return {false, plSpace};
        }         
        break;        
    }
    
    for (auto it = consumables.begin(); it != consumables.end(); /* update later */) {
        it->updateBB();
        bool coll = it->overlaps(player);
        if (coll) {
            plSpace.useConsumable(*it);
            it = consumables.erase(it); // Remove the consumed item using iterator
        } 
        else {
            it++;
        }
    }
    return {false, plSpace};
}

// Keyboard input processing routine
void keyInput(unsigned char key, int x, int y) {

    float tempX = cameraX;
    float tempY = cameraY;
    float tempZ = cameraZ;

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
        tempZ -= 1.0f; // Move forward
        break;
    case 's':
        tempZ += 1.0f; // Move backward
        break;
    case 'a':
        tempX -= 1.0f; // Move left
        break;
    case 'd':
        tempX += 1.0f; // Move right
        break;
    case 'z':
        tempY -= 1.0f; // Move down
        break;
    case 'x':
        tempY += 1.0f; // Move up
        break;
    case 27:
        exit(0); // Exit on ESC
        break;
    }

    SpaceCraft tempCraft = SpaceCraft(playerSpacecraft.getHealth(), playerSpacecraft.getDamage(),tempX, tempY, tempZ, true); 
    tempCraft.updateBB();
    
    std::pair<bool, SpaceCraft> re = detectCollision(tempCraft);
    bool coll = re.first;
    if (coll) {
        std::cout << "Collision Detected !!!!!!" << std::endl;
    }

    else{
        cameraX = tempX;
        cameraY = tempY;
        cameraZ = tempZ;
        //playerSpacecraft.setPosition(cameraX, cameraY, cameraZ);
        playerSpacecraft.setDamage(re.second.getDamage());
        playerSpacecraft.setHealth(re.second.getHealth());
    }

    glutPostRedisplay();
}

// Function to handle mouse input for camera rotation
void mouseMotion(int x, int y)
{
    static int lastX = -1;
    static int lastY = -1;

    if (lastX == -1 || lastY == -1)
    {
        lastX = x;
        lastY = y;
        return;
    }

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    cameraYaw += deltaX * 0.1f;
    cameraPitch += deltaY * 0.1f;

    if (cameraPitch > 90.0f)
        cameraPitch = 90.0f;
    if (cameraPitch < -90.0f)
        cameraPitch = -90.0f;

    lastX = x;
    lastY = y;
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL viewport coordinates
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glLoadIdentity();

        GLint viewport[4];
        GLdouble modelview[16], projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);


        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        Point source = Point(cameraX, cameraY, cameraZ);
        Point dist = Point(posX - cameraX, posY - cameraY, posZ - cameraZ);
        Projectile *proj = new Projectile(playerSpacecraft.getDamage(), true, source, dist);
        playerSpacecraft.shoot(&projectileManager, proj);
    }
}


// Timer function.
void clockTick(int value)
{

    latAngle += 1.0;
    if (latAngle > 360.0)
        latAngle -= 360.0;
    longAngle += 10.0;
    if (longAngle > 360.0)
        longAngle -= 360.0;
    
    bool secondPassed;
    static double lastTime = 0.0;  
    double currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    if (currentTime - lastTime >= 1.0) {
        lastTime = currentTime;
        secondPassed = true;
    } 
    else {
        secondPassed = false;
    }

    if (secondPassed) {
        enemySpaceCraftShooting();
    }
    
    endGame();
    glutPostRedisplay();
    glutTimerFunc(CLOCK_TICK_PERIOD, clockTick, value);
}

// Main routine
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Space War");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    //glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    clockTick(-1);
    glutMainLoop();
    return 0;
}
