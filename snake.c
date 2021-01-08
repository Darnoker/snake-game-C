#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "functions.h"

int main()
{
    clock_t t1 = clock();

    bool game = true;
    Tsnake snake;
    Tfood food;
    food.number = 0;
    int field[rows][columns];
    int score = 0;
    int highscore = 0;
    int var;
    int direction = 'd';

    snakeInit(&snake, field, &highscore);
    while (game)
    {
        clock_t t2 = clock();
        int deltaTime = (t2 - t1) * 0.0001;
        gameScreen(field, &score, &highscore, &snake);
        resetScreen();
        foodPrint(&food, field);
        movement(&var, &direction, &snake, field, &food, &score, &highscore, &game);
        tailManager(&snake, field);
        Sleep(deltaTime);
    }
    return 0;
}
