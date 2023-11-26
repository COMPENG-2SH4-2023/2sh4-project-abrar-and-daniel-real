#include "GameMechs.h"
#include <iostream>
#include <MacUILib.h>

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPosArrayList *blockOff)
{

    int candidX;
    int candidY;
    objPos tempPos; 
    bool generateFood; 
    srand((unsigned int)time(NULL));
    while (1)
    {
        generateFood = true; 
        int candidX = (rand() % (boardSizeX - 2)) + 2;
        int candidY = (rand() % (boardSizeY - 2)) + 2;

        for (int i = 0; i < blockOff->getSize(); i++)
        {
            blockOff->getElement(tempPos, i);
            if (candidX == tempPos.x && candidY == tempPos.y)
            {
                generateFood = false;
                break;  
            }
        }
        if(generateFood)
        {
            foodPos.setObjPos(candidX, candidY, '*');
            break;
        }
        else{
            continue; 
        }
    }
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}