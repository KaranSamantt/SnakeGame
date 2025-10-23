// Handles screen drawing and visuals
#include "game.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawColoredBoard() {
    setColor(3);
    int i;
    system("cls");
    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    for (i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) printf(" ");
        printf("#\n");
    }
    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    setColor(7);
}
