#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"    //are we allowed to do this????
#include "GameMechs.h" //are we allowed to do this????
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 10000000000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// declare global pointer to player
Player *myPlayer;
GameMechs *myMechs;
objPos myPos;

int main(void)
{

    Initialize();

    while (myMechs->getExitFlagStatus() == false)
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
    myMechs = new GameMechs(30, 15);
    myPlayer = new Player(myMechs);
    myMechs->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    myMechs->getInput();

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    myPlayer->movePlayer();

    myMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos myFoodPos;
    myMechs->getFoodPos(myFoodPos);
    for (int j = 1; j <= myMechs->getBoardSizeY(); j++)
    {

        for (int i = 1; i <= myMechs->getBoardSizeX(); i++)
        {
            drawn = false;
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (j == tempBody.y && i == tempBody.x)
                {

                    MacUILib_printf("@");
                    drawn = true;
                    break;
                }
            }

            if (drawn)
            {
                continue;
            }

            if (j == 1 || j == myMechs->getBoardSizeY() || i == 1 || i == myMechs->getBoardSizeX())
            {
                MacUILib_printf("#");
            }
            else if (i == myPos.x && j == myPos.y)
            {
                MacUILib_printf("%c", myPos.symbol);
            }
            else if (i == myFoodPos.x && j == myFoodPos.y)
            {
                MacUILib_printf("%c", myFoodPos.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("current pos and symbol for Player: [%d, %d] and %c \n", tempBody.x, tempBody.y, tempBody.symbol);
    MacUILib_printf("current pos and symbol for Food: [%d, %d] and %c \n", myFoodPos.x, myFoodPos.y, myFoodPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(7500000); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();
    delete myMechs;
    delete myPlayer;
}
