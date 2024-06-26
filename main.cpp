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
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

const unsigned int CLOCK_TICK_PERIOD = 30;

// Global variables
GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture, jupiterTexture, saturnTexture, uranusTexture, neptuneTexture, moonTexture;
GLuint spacecraftTexture, skyBoxTexture;
static int width, height; // Size of the OpenGL window.
float latAngle = 0;   // Definition
float longAngle = 0;  // Definition
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
float leftRightAngle = 0;

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
    skyBoxTexture = SOIL_load_OGL_texture("textures/skybox.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    SpaceCraft::texture = spacecraftTexture;
}

std::vector<CelestialObject> createCelestialObjects()
{
    std::vector<CelestialObject> celestialObjects;
    celestialObjects.emplace_back(10.0, sunTexture, 0.0, 0.0, 0.0);
    celestialObjects.emplace_back(0.8, mercuryTexture, 20.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.8, venusTexture, 25.0, 0.0, 0.0);
    celestialObjects.emplace_back(2.0, earthTexture, 30.0, 0.0, 0.0);
    celestialObjects.emplace_back(1.0, marsTexture, 35.0, 0.0, 0.0);
    celestialObjects.emplace_back(5.0, jupiterTexture, 45.0, 0.0, 0.0);
    celestialObjects.emplace_back(4.5, saturnTexture, 55.0, 0.0, 0.0);
    celestialObjects.emplace_back(3.5, uranusTexture, 65.0, 0.0, 0.0);
    celestialObjects.emplace_back(3.0, neptuneTexture, 75.0, 0.0, 0.0);
    return celestialObjects;
}

std::vector<SpaceCraft> createEnemySpacecrafts()
{
    std::vector<SpaceCraft> enemySpacecrafts;
    enemySpacecrafts.emplace_back(100, 10.0, 15.0, 15.0, -6.0, false);
    enemySpacecrafts.emplace_back(100, 10.0, 15.0, -15.0, -6.0, false);
    enemySpacecrafts.emplace_back(100, 10.0, -15.0, 15.0, -6.0, false);
    enemySpacecrafts.emplace_back(100, 10.0, -15.0, -15.0, -6.0, false);
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
    playerSpacecraft.setPosition(cameraX, cameraY, cameraZ + 1);
    playerSpacecraft.draw();

    // Draw the enemy spacecrafts
    for (SpaceCraft &enemySpacecraft : enemySpacecrafts)
    {
        Point oldPosition = enemySpacecraft.getPosition();
        Point direction = playerSpacecraft.getPosition() - enemySpacecraft.getPosition();
        float directionMagnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
        direction.x /= directionMagnitude;
        direction.y /= directionMagnitude;
        direction.z /= directionMagnitude;
        Point newPosition = enemySpacecraft.getPosition() + direction * 0.08;
        enemySpacecraft.setPosition(newPosition.x, newPosition.y, newPosition.z);
        if (enemySpacecraft.overlaps(playerSpacecraft.boundingSphere))
            enemySpacecraft.setPosition(oldPosition.x, oldPosition.y, oldPosition.z);
        enemySpacecraft.draw();
    }

    // Draw Consumables
    for (const auto &consumable : consumables)
    {
        consumable.draw();
    }
}

void drawSkybox() {
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, skyBoxTexture);
        glBegin(GL_QUADS);
        switch (i) {
            case 0:
                glTexCoord2f(0, 0); glVertex3f(500.0f, -500.0f, -500.0f);
                glTexCoord2f(1, 0); glVertex3f(500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 1); glVertex3f(500.0f, 500.0f, 500.0f);
                glTexCoord2f(0, 1); glVertex3f(500.0f, 500.0f, -500.0f);
                break;
            case 1:
                glTexCoord2f(0, 0); glVertex3f(-500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 0); glVertex3f(-500.0f, -500.0f, -500.0f);
                glTexCoord2f(1, 1); glVertex3f(-500.0f, 500.0f, -500.0f);
                glTexCoord2f(0, 1); glVertex3f(-500.0f, 500.0f, 500.0f);
                break;
            case 2:
                glTexCoord2f(0, 0); glVertex3f(-500.0f, 500.0f, -500.0f);
                glTexCoord2f(1, 0); glVertex3f(500.0f, 500.0f, -500.0f);
                glTexCoord2f(1, 1); glVertex3f(500.0f, 500.0f, 500.0f);
                glTexCoord2f(0, 1); glVertex3f(-500.0f, 500.0f, 500.0f);
                break;
            case 3:
                glTexCoord2f(0, 0); glVertex3f(-500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 0); glVertex3f(500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 1); glVertex3f(500.0f, -500.0f, -500.0f);
                glTexCoord2f(0, 1); glVertex3f(-500.0f, -500.0f, -500.0f);
                break;
            case 4:
                glTexCoord2f(0, 0); glVertex3f(-500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 0); glVertex3f(500.0f, -500.0f, 500.0f);
                glTexCoord2f(1, 1); glVertex3f(500.0f, 500.0f, 500.0f);
                glTexCoord2f(0, 1); glVertex3f(-500.0f, 500.0f, 500.0f);
                break;
            case 5:
                glTexCoord2f(0, 0); glVertex3f(500.0f, -500.0f, -500.0f);
                glTexCoord2f(1, 0); glVertex3f(-500.0f, -500.0f, -500.0f);
                glTexCoord2f(1, 1); glVertex3f(-500.0f, 500.0f, -500.0f);
                glTexCoord2f(0, 1); glVertex3f(500.0f, 500.0f, -500.0f);
                break;
        }
        glEnd();
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
            PlaySound(TEXT("sounds/hit.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
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
        menu.writeGameOver(-1, 0.0, -2.0, isWinner[winner]);
        glutSwapBuffers();
        PlaySound(TEXT("sounds/gameover.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
        return;
    }

    // Dispaly Game Options
    if (!started)
    {
        cameraY = 20.0f;
        cameraX = 0.0f;
        cameraZ = 50.0f;
        leftRightAngle = 0;
        menu.writeMenuOptions();
        glutSwapBuffers();
        return;
    }

    // Begin Main viewport. 
    glViewport(0, 0, width, height);
    glLoadIdentity();

    // Draw the player health bar
    healthBar.drawPlayerHealthBar(playerSpacecraft.getHealth());

    gluLookAt(cameraX,
              cameraY,
              cameraZ,
              cameraX - sin((M_PI / 180.0) * leftRightAngle),
              cameraY,
              cameraZ - cos((M_PI / 180.0) * leftRightAngle),
              0.0,
              1.0,
              0.0);

    // Draw objects in the main viewport
    detectProjectileCollision();
    projectileManager.notifyClockTick();
    drawObjects();

    drawSkybox();

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
    playerSpacecraft = SpaceCraft(100, 10, cameraX, cameraY, cameraZ + 1, true);
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
    float tempLeftRightAngle = leftRightAngle;

    switch (key) {
    // Menu buttons
    case 13: // Start on Enter
        if (started)
            return;
        started = true;
        PlaySound(TEXT("sounds/menu.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
        glutPostRedisplay();
        break;
    case 'l':
        if (started)
            return;
        menu.toggleLevel();
        PlaySound(TEXT("sounds/menu.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
        glutPostRedisplay();
        break;
    case 'm':
        if (started)
            return;
        menu.toggleMode();
        PlaySound(TEXT("sounds/menu.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
        glutPostRedisplay();
        break;
    case 'w':
		tempX = cameraX - sin(leftRightAngle * M_PI / 180.0);
		tempZ = cameraZ - cos(leftRightAngle * M_PI / 180.0);
        break;
    case 's':
		tempX = cameraX + sin(leftRightAngle * M_PI / 180.0);
		tempZ = cameraZ + cos(leftRightAngle * M_PI / 180.0);
        break;
    case 'a':
        tempLeftRightAngle += 5;
        break;
    case 'd':
        tempLeftRightAngle -= 5;
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

	if (leftRightAngle > 360)
		leftRightAngle -= 360;
	else if (leftRightAngle < 0)
		leftRightAngle += 360;

    SpaceCraft tempCraft = SpaceCraft(playerSpacecraft.getHealth(), playerSpacecraft.getDamage(), tempX, tempY, tempZ + 1, true);
    tempCraft.updateBB();
    
    std::pair<bool, SpaceCraft> re = detectCollision(tempCraft);
    bool coll = re.first;
    if (coll) {
        PlaySound(TEXT("sounds/collision.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
        std::cout << "Collision Detected !!!!!!" << std::endl;
    }

    else{
        cameraX = tempX;
        cameraY = tempY;
        cameraZ = tempZ;
        leftRightAngle = tempLeftRightAngle;
        playerSpacecraft.setDamage(re.second.getDamage());
        playerSpacecraft.setHealth(re.second.getHealth());
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (!started)
        return;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        PlaySound(TEXT("sounds/gun.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_NOSTOP);
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

        Point source = playerSpacecraft.getPosition();
        Point direction = Point(posX - source.x, posY - source.y, posZ - source.z);
        Projectile *proj = new Projectile(playerSpacecraft.getDamage(), true, source, direction);
        playerSpacecraft.shoot(&projectileManager, proj);
    }
}


// Timer function.
void clockTick(int value)
{
    glutTimerFunc(CLOCK_TICK_PERIOD, clockTick, value);
    if (gameOver || (!started))
        return;

    latAngle += 0.5;
    if (latAngle > 360.0)
        latAngle -= 360.0;
    longAngle += 0.5;
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
    glutMouseFunc(mouseClick);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    clockTick(-1);
    glutMainLoop();
    return 0;
}
