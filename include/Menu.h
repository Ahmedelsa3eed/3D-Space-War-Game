#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
private:

    char theStringBuffer[15]; // String buffer.

public:

    void *font;                // Font selection.

    enum { EASY, HARD };             // game level
    int level;

    enum { SURVIVAL, TIME_ATTACK };  // game mode
    int mode;

    Menu();

    int getLevel();

    void toggleLevel();

    int getMode();

    void toggleMode();

    void writeBitmapString(void *font, char *string);

    void printGameLevel(float x, float y, float z);

    void printGameMode(float x, float y, float z);

    void printStartGameOption(float x, float y, float z);

    void writeGameOver(float x, float y, float z, std::string winStatus);

    void writeMenuOptions(void);
};

#endif