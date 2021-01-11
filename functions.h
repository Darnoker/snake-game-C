#include <stdio.h>

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
int getKey();
void tailManager(Tsnake *, int field[][columns]);
void gameOver(int *, bool *, int *);
void hidecursor();