#ifndef MENU_H
#define MENU_H

class Menu {
private:

    char theStringBuffer[15]; // String buffer.

public:

    long font;                // Font selection.

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

    void printGameLevel();

    void printGameMode();

    void printStartGameOption();

    void writeMenuOptions(void);
};

#endif