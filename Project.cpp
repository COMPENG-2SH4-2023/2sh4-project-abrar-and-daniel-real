#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"   
#include "GameMechs.h" 
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 0.5

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// declare global pointer to Player & GameMechs object(s)
Player *myPlayer;
GameMechs *myMechs;

int main(void)
{

    Initialize();

    //Check status of exit flag and lose flag
    while (myMechs->getExitFlagStatus() == false && myMechs->getLoseFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();

    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Intatialize board size and heap members
    myMechs = new GameMechs(30, 15);
    myPlayer = new Player(myMechs);
    //Initialize food bucket generation
    myMechs->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    //Get input routine
    myMechs->getInput();
}

void RunLogic(void)
{
    //Update the current player direction
    myPlayer->updatePlayerDir();

    //Update the current player position
    myPlayer->movePlayer();

    //Clear the current input out of the iostream 
    myMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    //declare two objPosArrayList pointers to two objects
    //Use one object to retrieve and hold the most recent array list representing the player's body
    //Use another object to retrieve and store the hold recent array list representing the food bucket
    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPosArrayList *foodBucket = myMechs->getFoodBucket();
    
    //declare two temporary objects 
    //tempBody will track the position of the player body
    //myFoodPos will track the position of a food object
    objPos tempBody;
    objPos myFoodPos;

    MacUILib_printf("Bonus Iteration: Superfood Information \n \n");
    MacUILib_printf("* --> increase player score and size by 1 \n \n");
    MacUILib_printf("+ --> increase player score by 10 \n \n");
    MacUILib_printf("- --> If player size is 5 or greater (not including head), shrink player size by 5 and lower score by 5 \n \n");
    MacUILib_printf("Every newly generated board will contain a maximum of 2 superfood(s) \n \n");

    //iterating through rows after iterating through all the columns in each row
    for (int j = 1; j <= myMechs->getBoardSizeY(); j++)
    {

        //iterating through all the columns in each row
        for (int i = 1; i <= myMechs->getBoardSizeX(); i++)
        {
            //update draw status
            drawn = false;

            //iterate through the food bucket
            for (int l = 0; l <= foodBucket->getSize(); l++)
            {
                //  update the food position object to hold the x-y position of the element currently being iterated 
                //  through in the food bucket array list (index l)
                foodBucket->getElement(myFoodPos, l);

                //check if food symbol is to be drawn on the screen
                if (j == myFoodPos.y && i == myFoodPos.x)
                {

                    //drawing food and updating drawing status
                    MacUILib_printf("%c", myFoodPos.symbol);
                    drawn = true;
                    break;
                }
            }
            //iterate through the player body array list
            for (int k = 0; k < playerBody->getSize(); k++)
            {

                //  update the tempBody object to hold the x-y position of the element currently being iterated 
                //  through in the array list of the player body (index k)
                playerBody->getElement(tempBody, k);

                //check if player symbol is to be drawn
                if (j == tempBody.y && i == tempBody.x)
                {

                    //draw player symbol and update status
                    MacUILib_printf("@");
                    drawn = true;
                    break;
                }
            }

            //continue checking for more player body and food symbols to draw if either has been drawn 
            if (drawn)
            {
                continue;
            }

            //check if drawing the border is needed
            if (j == 1 || j == myMechs->getBoardSizeY() || i == 1 || i == myMechs->getBoardSizeX())
            {
                //drawing the border
                MacUILib_printf("#");
            }

            //draw empty space on the board if drawing the border is not needed 
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    };

    //print the player score
    MacUILib_printf("Score: %d", myMechs->getScore());
    
    //check if the player has lost
    if (myMechs->getLoseFlagStatus() == true)
    {
        //print final message
        MacUILib_printf("\nGame Over!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(20000); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();
    delete myMechs;
    delete myPlayer;
}
