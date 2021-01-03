#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define rows 20
#define columns 60

typedef struct
{
    int x;
    int y;
    int head;
    int tail;
    int Gx;

} Tsnake;

typedef struct
{
    int x;
    int y;
    int number;

} Tfood;

void gameScreen(int field[][columns], int *, int *, Tsnake *);
void snakeInit(Tsnake *, int field[][columns], int *);
void resetScreen();
void foodPrint(Tfood *, int field[][columns]);
void movement(int *, int *, Tsnake *, int field[][columns], Tfood *, int *, int *, bool *);
int getch_noblock();
void tailRemover(Tsnake *, int field[][columns]);
void gameOver(int *, bool *, int *);

int main()
{
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
        gameScreen(field, &score, &highscore, &snake);
        resetScreen();
        foodPrint(&food, field);
        movement(&var, &direction, &snake, field, &food, &score, &highscore, &game);
        tailRemover(&snake, field);
        Sleep(32);
    }
    return 0;
}

void snakeInit(Tsnake *snake, int field[][columns], int *highscore) //Inicjalizacja Snake'a
{
    FILE *file;
    file = fopen("high-score.txt", "r");
    fscanf(file, "%d", &*highscore);
    fclose(file);

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            field[row][column] = 0;
        }
    }
    snake->x = columns / 2;
    snake->y = rows / 2;
    snake->head = 5;
    snake->tail = 1;
    snake->Gx = snake->x;

    for (size_t i = 0; i < snake->head; i++)
    {
        snake->Gx++;
        field[snake->y][snake->Gx - snake->head] = i + 1;
    }
}

void gameScreen(int field[][columns], int *score, int *highscore, Tsnake *snake)
{
    for (size_t column = 0; column <= columns + 1; column++) // Narysowanie góry planszy
    {
        if (column == 0)
            printf("%c", 201);
        else if (column == columns + 1)
            printf("%c", 187);
        else
            printf("%c", 205);
    }

    printf("Wynik: %d |  Najwyszy wynik: %d", *score, *highscore);
    printf("\n");

    for (size_t row = 0; row < rows; row++) //Narysowanie boków planszy
    {
        printf("%c", 186);
        for (size_t column = 0; column < columns; column++) //Rysownaie boków i snake'a
        {
            if (field[row][column] == 0)
                printf(" ");
            if (field[row][column] > 0 && field[row][column] != snake->head)
                printf("%c", 176);
            if (field[row][column] == snake->head)
                printf("%c", 178);
            if (field[row][column] == -1)
                printf("%c", 15);
            if (column == columns - 1)
                printf("%c\n", 186);
        }
    }
    for (size_t column = 0; column <= columns + 1; column++) //Narysowanie dołu planszy
    {
        if (column == 0)
            printf("%c", 200);
        else if (column == columns + 1)
            printf("%c", 188);
        else
            printf("%c", 205);
    }
}

void resetScreen() //Odswiezanie ekranu gry
{
    HANDLE hOut;
    COORD position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(hOut, position);
}

void foodPrint(Tfood *food, int field[][columns]) //Rysowanie jedzenia na ekranie
{
    srand(time(0));
    food->y = (rand() % (rows - 2)) + 1;
    food->x = (rand() % (columns - 2)) + 1;

    if (food->number == 0 && field[food->y][food->x] == 0)
    {
        field[food->y][food->x] = -1;
        food->number = 1;
    }
}

void movement(int *var, int *direction, Tsnake *snake, int field[][columns], Tfood *food, int *score, int *highscore, bool *game) //Poruszanie sie gracza
{

    *var = getch_noblock();
    *var = tolower(*var);

    if (((*var == 'd' || *var == 'a') || (*var == 'w' || *var == 's')) && (abs(*direction - *var) > 5)) //sprawdzanie wartosci ASCII pomiedzy wcisnietymi klawiszami
        *direction = *var;

    if ((char)*direction == 'd')
    {
        snake->x++;
        if (field[snake->y][snake->x] != 0 && field[snake->y][snake->x] != -1)
            gameOver(score, game, highscore);
        if (snake->x == columns - 1)
            snake->x = 0;
        if (field[snake->y][snake->x] == -1)
        {
            food->number = 0;
            snake->tail -= 2;
            *score += 1;
        }
        snake->head++;
        field[snake->y][snake->x] = snake->head;
    }

    if ((char)*direction == 'a')
    {
        snake->x--;
        if (field[snake->y][snake->x] != 0 && field[snake->y][snake->x] != -1)
            gameOver(score, game, highscore);

        if (snake->x == 0)
            snake->x = columns - 1;

        if (field[snake->y][snake->x] == -1)
        {
            food->number = 0;
            snake->tail -= 2;
            *score += 1;
        }
        snake->head++;
        field[snake->y][snake->x] = snake->head;
    }

    if ((char)*direction == 'w')
    {
        snake->y--;
        if (field[snake->y][snake->x] != 0 && field[snake->y][snake->x] != -1)
            gameOver(score, game, highscore);
        if (snake->y == -1)
            snake->y = rows - 1;
        if (field[snake->y][snake->x] == -1)
        {
            food->number = 0;
            snake->tail -= 2;
            *score += 1;
        }
        snake->head++;
        field[snake->y][snake->x] = snake->head;
    }

    if ((char)*direction == 's')
    {
        snake->y++;
        if (field[snake->y][snake->x] != 0 && field[snake->y][snake->x] != -1)
            gameOver(score, game, highscore);
        if (snake->y == rows - 1)
            snake->y = 0;
        if (field[snake->y][snake->x] == -1)
        {
            food->number = 0;
            snake->tail -= 2;
            *score += 1;
        }
        snake->head++;
        field[snake->y][snake->x] = snake->head;
    }
}
int getch_noblock()
{ //Funkcja pobierajaca klawisz
    if (_kbhit())
        return getch();
    else
        return -1;
}

void tailRemover(Tsnake *snake, int field[][columns])
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (field[i][j] == snake->tail)
            {
                field[i][j] = 0;
            }
        }
    }
    snake->tail++;
}

void gameOver(int *score, bool *game, int *highscorek)
{
    FILE *file;
    file = fopen("high-score.txt", "r");
    fscanf(file, "%d", &*highscorek);
    fclose(file);

    printf("\a");
    Sleep(1500);
    system("cls");

    printf("      GAME OVER !!!!!!!!!!!!\n");

    *game = false;

    if (*score > *highscorek)
    {
        printf("Nowy najwyzszy wynik! %d\n", *score);
        file = fopen("high-score.txt", "w");
        fprintf(file, "\n%d", *score);
        fclose(file);
    }
    else
    {
        printf("Wynik: %d\n", *score);
    }

    system("pause");
}