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
int field[rows][columns];
bool game = true;
int var;
int direction = 'd';
int score = 0;
int highscore = 0;
FILE *file;

typedef struct
{
    int x;
    int y;
    int head;
    int tail;
    int Gy;

} Tsnake;

typedef struct
{
    int x;
    int y;
    int number;

} TFood;

Tsnake snake;
TFood food;

void gameScreen();
void snakeInit();
void resetScreen();
void foodPrint();
void movement();
int getch_noblock();
void tailRemover();
void checkFood();
void checkBody();
void gameOver();

int main()
{
    snakeInit();
    while (game)
    {
        gameScreen();
        resetScreen();
        foodPrint();
        movement();
        tailRemover();
        Sleep(32);
    }
    return 0;
}

void snakeInit() //Inicjalizacja Snake'a
{
    file = fopen("high-score.txt", "r");
    fscanf(file,"%d", &highscore);
    fclose(file);
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            field[row][column] = 0;
        }
    }
    snake.x = rows / 2;
    snake.y = columns / 2;
    snake.head = 5;
    snake.tail = 1;
    snake.Gy = snake.y;

    for (size_t i = 0; i < snake.head; i++)
    {
        snake.Gy++;
        field[snake.x][snake.Gy - snake.head] = i + 1;
    }
}

void gameScreen()
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

    printf("Wynik: %d |  Najwyszy wynik: %d", score, highscore); 
    printf("\n");

    for (size_t row = 0; row < rows; row++) //Narysowanie boków planszy
    {
        printf("%c", 186);
        for (size_t column = 0; column < columns; column++) //Rysownaie boków i snake'a
        {
            if (field[row][column] == 0)
                printf(" ");
            if (field[row][column] > 0 && field[row][column] != snake.head)
                printf("%c", 176);
            if (field[row][column] == snake.head)
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
void foodPrint() //Rysowanie jedzenia na ekranie
{
    srand(time(0));
    food.x = (rand() % (rows - 2)) + 1;
    food.y = (rand() % (columns - 2)) + 1;

    if (food.number == 0 && field[food.x][food.y] == 0)
    {
        field[food.x][food.y] = -1;
        food.number = 1;
    }
}

void movement() //Poruszanie sie gracza
{
    var = getch_noblock();
    var = tolower(var);
    if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(direction - var) > 5)) //sprawdzanie wartosci ASCII pomiedzy wcisnietymi klawiszami
        direction = var;

    switch (direction)
    {
    case 'd':
        snake.y++;
        checkBody();
        if (snake.y == columns - 1)
            snake.y = 0;
        checkFood();
        snake.head++;
        field[snake.x][snake.y] = snake.head;
        break;

    case 'a':
        snake.y--;
        checkBody();
        if (snake.y == 0)
            snake.y = columns - 1;
        checkFood();
        snake.head++;
        field[snake.x][snake.y] = snake.head;
        break;

    case 'w':
        snake.x--;
        checkBody();
        if (snake.x == -1)
            snake.x = rows - 1;
        checkFood();
        snake.head++;
        field[snake.x][snake.y] = snake.head;
        break;

    case 's':
        snake.x++;
        checkBody();
        if (snake.x == rows - 1)
            snake.x = 0;
        checkFood();
        snake.head++;
        field[snake.x][snake.y] = snake.head;
        break;
    }
}
int getch_noblock()
{ //Funkcja pobierajaca klawisz
    if (_kbhit())
        return getch();
    else
        return -1;
}

void tailRemover()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (field[i][j] == snake.tail)
            {
                field[i][j] = 0;
            }
        }
    }
    snake.tail++;
}
void checkFood()
{
    if (field[snake.x][snake.y] == -1)
    {
        food.number = 0;
        snake.tail -= 2;
        score += 1;

    }   
}
void checkBody()
{
    if (field[snake.x][snake.y] != 0 && field[snake.x][snake.y] != -1)
        gameOver();
}
void gameOver()
{
    printf("\a");
    Sleep(1500);
    system("cls");

    printf("      GAME OVER !!!!!!!!!!!!\n");

    game = false;

    if (score > highscore)
    {
        printf("Nowy najwyzszy wynik! %d\n", score);
        file = fopen("high-score.txt", "w");
        fprintf(file, "\n%d", score);
        fclose(file);
    }
    else
    {
        printf("Wynik: %d\n", score);
    }
    
    system("pause");
}