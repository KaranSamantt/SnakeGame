// The main file to run the game
#include "game.h"

void instructions() {
    system("cls");
    printf("==============================\n");
    printf("        🐍 INSTRUCTIONS 🐍     \n");
    printf("==============================\n");
    printf("\n-> Use W, A, S, D to move the snake");
    printf("\n-> Eat food (O) to grow and score points");
    printf("\n-> Avoid hitting walls or yourself");
    printf("\n-> Press X anytime to exit the game");
    printf("\n\nPress any key to return to menu...");
    _getch();
}

void startGame() {
    struct Snake snake;
    int foodX, foodY;
    int gameOver = 0, score = 0;

    system("cls");
    drawColoredBoard();
    initSnake(&snake);
    generateFood(&foodX, &foodY);

    while (!gameOver) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' && snake.dir != DOWN) snake.dir = UP;
            else if (ch == 's' && snake.dir != UP) snake.dir = DOWN;
            else if (ch == 'a' && snake.dir != RIGHT) snake.dir = LEFT;
            else if (ch == 'd' && snake.dir != LEFT) snake.dir = RIGHT;
            else if (ch == 'x') gameOver = 1;
            Beep(400, 600);  // 🔴 Low tone for game over
             // Exit
        }

        moveSnake(&snake);
        gameOver = checkCollision(&snake);

        if (checkFood(&snake, foodX, foodY)) {
            score += 10;
            generateFood(&foodX, &foodY);
            Beep(900, 100);  // 🎵 Play short beep when food is eaten
            }


        showScore(score);
        int speed = 150 - (score / 50) * 15;
        if (speed < 50) speed = 50;
        delay(speed);
    }

    saveScore(score);
    system("cls");
    printf("\nGame Over! Your final score: %d\n", score);
    showHighScores();
    printf("\nPress any key to return to menu...");
    _getch();
}

int main() {
    int choice;

    while (1) {
        system("cls");
        playWelcomeMusic();
        setColor(10);
        printf("====================================\n");
        printf("          🐍 SNAKE GAME 🐍           \n");
        printf("====================================\n");
        setColor(7);
        printf("1. Start Game\n");
        printf("2. Instructions\n");
        printf("3. High Scores\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                instructions();
                break;
            case 3:
                system("cls");
                showHighScores();
                printf("\nPress any key to return...");
                _getch();
                break;
            case 4:
                system("cls");
                printf("Thanks for playing! Goodbye 🐍\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
                delay(1000);
        }
    }

    return 0;
}
