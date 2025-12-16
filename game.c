#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

int height = 20, width = 40;
int x, y, foodX, foodY, score;
int gameOver;
char direction;

void setup() {
    gameOver = 0;
    direction = 's';
    x = width / 2;
    y = height / 2;
    foodX = rand() % (width - 2) + 1;
    foodY = rand() % (height - 2) + 1;
    score = 0;
}

void draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == foodY && j == foodX)
                printf("F");
            else
                printf(" ");

            if (j == width - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < width + 2; i++)
        printf("#");

    printf("\nScore: %d", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direction = 'l';
            break;
        case 'd':
            direction = 'r';
            break;
        case 'w':
            direction = 'u';
            break;
        case 's':
            direction = 'd';
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void logic() {
    switch (direction) {
    case 'l':
        x--;
        break;
    case 'r':
        x++;
        break;
    case 'u':
        y--;
        break;
    case 'd':
        y++;
        break;
    default:
        break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = 1;

    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    printf("\nGame Over!");
    return 0;
}
