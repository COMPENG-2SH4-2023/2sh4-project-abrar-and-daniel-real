#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"    //are we allowed to do this????
#include "GameMechs.h" //are we allowed to do this????

using namespace std;

#define DELAY_CONST 10000000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// declare global pointer to player
Player *myPlayer;
objPos myPos;
GameMechs *myMechs;

int main(void)
{

    Initialize();

    while (exitFlag == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();

        // initialize player object on the heap
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    // initialize player here
    myMechs = new GameMechs();
    myPlayer = new Player(myMechs);

    exitFlag = false;
}

void GetInput(void)
{
}

void RunLogic(void)
{
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i = 0;
    int j = 0;
    MacUILib_printf("current pos and symbol: [%d, %d] and %c \n", myPos.x, myPos.y, myPos.symbol);
    for (j = 0; j < 10; j++)
    {

        for (i = 0; i < 20; i++)
        {
            myPlayer->getPlayerPos(myPos);
            if (j == 0 || j == 10 - 1 || i == 0 || i == 20 - 1)
            {
                MacUILib_printf("#");
            }
            else if (i == myPos.x && j == myPos.y)
            {
                MacUILib_printf("%c", myPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();
}
