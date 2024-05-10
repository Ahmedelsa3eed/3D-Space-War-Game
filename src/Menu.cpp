
#include "Menu.h"
#include <iostream>
#include <GL/freeglut.h>

Menu::Menu() {
    font = 3;
    level = EASY;
    mode = SURVIVAL;
}

void Menu::writeBitmapString(void *font, char *string) {
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void Menu::printGameLevel() {
	// get Game Level
	if (level == EASY) {
		sprintf(theStringBuffer, "%s", "Easy");
	}
	else {
		sprintf(theStringBuffer, "%s", "Hard");
	}
	theStringBuffer[4] = '\0';

	glRasterPos3f(-1.0, 1.05, -2.0);
	writeBitmapString((void*)font, "Press 'l' to toggle the level difficulty Easy/Hard: ");
	writeBitmapString((void*)font, theStringBuffer);
}

void Menu::printGameMode() {
	// get Game Mode
	if (mode == SURVIVAL) {
		sprintf(theStringBuffer, "%s", "Survival");
	}
	else {
		sprintf(theStringBuffer, "%s", "Time-attack");
	}
	theStringBuffer[11] = '\0';

	glRasterPos3f(-1.0, 0.97, -2.0);
	writeBitmapString((void*)font, "Press 'm' to toggle the game mode Survival/Time-attack: ");
	writeBitmapString((void*)font, theStringBuffer);
}

void Menu::printStartGameOption() {
    glRasterPos3f(-1.0, 0.89, -2.0);
    writeBitmapString((void*)font, "Press 'Enter' to start the Game");
}

// write game options to screen
void Menu::writeMenuOptions(void) {
	glColor3f(1.0, 1.0, 1.0);

	printGameLevel();
	printGameMode();
    printStartGameOption();
}

int Menu::getLevel() {
    return level;
}

void Menu::toggleLevel() {
    level = 1 - level;
}

int Menu::getMode() {
    return mode;
}

void Menu::toggleMode() {
    mode = 1 - mode;
}