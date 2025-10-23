// Handles score saving and file operations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define MAX_SCORES 5
#define FILE_NAME "highscores.txt"

struct Score {
    char name[30];
    int points;
};

void saveScore(int score) {
    struct Score scores[MAX_SCORES];
    struct Score newScore;
    FILE *file;
    int count = 0;

    printf("\nEnter your name: ");
    scanf("%s", newScore.name);
    newScore.points = score;

    // Read existing scores
    file = fopen(FILE_NAME, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d", scores[count].name, &scores[count].points) == 2) {
            count++;
            if (count >= MAX_SCORES) break;
        }
        fclose(file);
    }

    // Add new score
    scores[count++] = newScore;

    // Sort scores (highest first)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].points > scores[i].points) {
                struct Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Save top scores
    file = fopen(FILE_NAME, "w");
    if (file == NULL) return;
    for (int i = 0; i < count && i < MAX_SCORES; i++) {
        fprintf(file, "%s %d\n", scores[i].name, scores[i].points);
    }
    fclose(file);
}

void showHighScores() {
    FILE *file = fopen(FILE_NAME, "r");
    struct Score s;
    int rank = 1;

    printf("=========================\n");
    printf("     🏆 HIGH SCORES 🏆    \n");
    printf("=========================\n");

    if (file == NULL) {
        printf("\nNo scores yet! Play a game to create one.\n");
        return;
    }

    while (fscanf(file, "%s %d", s.name, &s.points) == 2) {
        printf("%d. %-10s  %d\n", rank++, s.name, s.points);
        if (rank > MAX_SCORES) break;
    }

    fclose(file);
}
