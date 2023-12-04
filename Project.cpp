#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"    //are we allowed to do this????
#include "GameMechs.h" //are we allowed to do this????
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 0.99

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// declare global pointer to player
Player *myPlayer;
GameMechs *myMechs;

int main(void)
{

    Initialize();

    while (myMechs->getExitFlagStatus() == false && myMechs->getLoseFlagStatus() == false)
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
    objPosArrayList *foodBucket = myMechs->getFoodBucket();
    objPos tempBody;
    objPos myFoodPos;

    for (int j = 1; j <= myMechs->getBoardSizeY(); j++)
    {

        for (int i = 1; i <= myMechs->getBoardSizeX(); i++)
        {
            drawn = false;

            for (int l = 0; l <= foodBucket->getSize(); l++)
            {
                foodBucket->getElement(myFoodPos, l);
                if (j == myFoodPos.y && i == myFoodPos.x)
                {

                    MacUILib_printf("%c", myFoodPos.symbol);
                    drawn = true;
                    break;
                }
            }
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

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    };
    MacUILib_printf("Score: %d", myMechs->getScore());
    if (myMechs->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nGame Over!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();
    delete myMechs;
    delete myPlayer;
}
