// Snake movement, logic, food, collision
#include <windows.h>  // for Beep()
#include "game.h"
void playWelcomeMusic() {
    // Frequencies in Hz for simple melody
    int notes[] = {523, 587, 659, 698, 784, 880, 988};
    int duration = 150; // milliseconds
    int i;

    for (i = 0; i < 5; i++) { // play first 5 notes as a short melody
        Beep(notes[i], duration);
        Sleep(50); // short pause between notes
    }
}


#define WIDTH 50
#define HEIGHT 25

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}

void drawBoard() {
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
}

void initSnake(struct Snake *snake) {
    snake->length = 3;
    snake->x[0] = WIDTH / 2;
    snake->y[0] = HEIGHT / 2;
    snake->dir = RIGHT;
    for (int i = 1; i < snake->length; i++) {
        snake->x[i] = snake->x[i - 1] - 1;
        snake->y[i] = snake->y[i - 1];
    }
}

void generateFood(int *foodX, int *foodY) {
    *foodX = rand() % WIDTH + 1;
    *foodY = rand() % HEIGHT + 1;
    gotoxy(*foodX, *foodY);
    setColor(4); // red
    printf("O");
    setColor(7); // reset
}


void moveSnake(struct Snake *snake) {
    int i;
    // Erase tail
    gotoxy(snake->x[snake->length - 1], snake->y[snake->length - 1]);
    printf(" ");

    // Shift body
    for (i = snake->length - 1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    // Move head
    if (snake->dir == UP) snake->y[0]--;
    else if (snake->dir == DOWN) snake->y[0]++;
    else if (snake->dir == LEFT) snake->x[0]--;
    else if (snake->dir == RIGHT) snake->x[0]++;

    // Draw head (green)
    gotoxy(snake->x[0], snake->y[0]);
    setColor(10);
    printf("@");

    // Draw body (light green)
    setColor(2);
    for (i = 1; i < snake->length; i++) {
        gotoxy(snake->x[i], snake->y[i]);
        printf("o");
    }

    setColor(7); // reset color
}

int checkCollision(struct Snake *snake) {
    // Wall collision
    if (snake->x[0] <= 0 || snake->x[0] >= WIDTH + 1 ||
        snake->y[0] <= 0 || snake->y[0] >= HEIGHT + 1)
        return 1;

    // Self collision
    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
            return 1;
    }

    return 0;
}

int checkFood(struct Snake *snake, int foodX, int foodY) {
    if (snake->x[0] == foodX && snake->y[0] == foodY) {
        snake->length++;
        snake->x[snake->length - 1] = snake->x[snake->length - 2];
        snake->y[snake->length - 1] = snake->y[snake->length - 2];
        return 1;
    }
    return 0;
}

void showScore(int score) {
    gotoxy(0, HEIGHT + 3);
    printf("Score: %d", score);
}
