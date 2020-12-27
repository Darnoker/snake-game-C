#include <stdio.h>


#define columns 10
#define rows 10
int field[columns][rows];

typedef struct 
{
    int x;
    int y;
    int head;
    int tail;
    int Gy;
    
} Tsnake;


void Field();
void snakeInit();

int main()
{
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

    Tsnake snake;
    snake.x = columns/2;
    snake.y = rows/2;
    snake.head = 5;
    snake.tail = 1;
    snake.Gy = snake.y;

    for (size_t i = 0; i < snake.head; i++)
    {
       snake.Gy++;
       field[snake.x][snake.Gy - snake.head] = i+1;
    }
    
}

void Field()
{
    for (size_t row = 0; row <= rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            if (row == 0)
            {
                if (column == 0)
                    printf("%c", 201);

                else if (column > 0 && column < columns - 1)
                    printf("%c", 205);

                else 
                    printf("%c", 187);
            }
            else if (row > 0 && row < rows - 1)
            {
                if (column == 0 || column == columns - 1)
                    printf("%c", 186);

                else
                    printf(" ");
            }
            else if (row == rows - 1)
            {
                if (column == 0)
                    printf("%c", 200);

                else if (column > 0 && column < columns - 1)
                    printf("%c", 205);

                else 
                    printf("%c", 188);
            }
        }
        printf("\n");
    }
}