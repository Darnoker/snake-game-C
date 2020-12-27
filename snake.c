#include <stdio.h>


#define rows 20
#define columns 40
int field[rows][columns];

typedef struct 
{
    int x;
    int y;
    int head;
    int tail;
    int Gx;
    
} Tsnake;

Tsnake snake;


void plansza();
void snakeInit();

int main()
{
    snakeInit();
    plansza();
    

    return 0;
}

void snakeInit()
{
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            field[row][column] = 0;
        }
    }
    snake.x = columns/2;
    snake.y = rows/2;
    snake.head = 5;
    snake.tail = 1;
    snake.Gx = snake.x;

    for (size_t i = 0; i < snake.head; i++)
    {
       snake.Gx++;
       field[snake.y][snake.Gx - snake.head] = i+1;
    }
}

void plansza()
{
    for (size_t column = 0; column <= columns+1; column++) // Narysowanie góry planszy
    {
        if (column == 0)
            printf("%c", 201);
        else if (column == columns + 1)
            printf("%c", 187);
        else
            printf("%c", 205);
    }

    printf("\n");

    for (size_t row = 0; row < rows; row++) //Narysowanie boków planszy
    {
        printf("%c", 186);
        for (size_t column = 0; column < columns; column++)
        {
            if (field[row][column] == 0)
                printf(" ");
            if (field[row][column] > 0 && field[row][column] != snake.head)
                printf("%c", 176);
            if (field[row][column] == snake.head)
                printf("%c", 178);
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

