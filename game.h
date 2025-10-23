// Function declarations and global structures
#ifndef GAME_H
#define GAME_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Snake structure
struct Snake {
    int x[100];
    int y[100];
    int length;
    int dir;
};

void gotoxy(int x, int y);
void delay(int milliseconds);
void drawBoard();
void initSnake(struct Snake *snake);
void moveSnake(struct Snake *snake);
void generateFood(int *foodX, int *foodY);
int checkCollision(struct Snake *snake);
int checkFood(struct Snake *snake, int foodX, int foodY);
void showScore(int score);

void setColor(int color);
void drawColoredBoard();
#define WIDTH 50
#define HEIGHT 25

void instructions();
void startGame();

void saveScore(int score);
void showHighScores();


#endif
