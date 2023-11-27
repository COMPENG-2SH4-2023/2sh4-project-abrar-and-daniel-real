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

    foodBucket = new objPosArrayList();
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;

    foodBucket = new objPosArrayList();
}

GameMechs::~GameMechs()
{
    delete foodBucket;
}
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

void GameMechs::incrementScoreTwo(int x)
{
    score += x;
}

void GameMechs::generateFood(objPosArrayList *blockOff)
{
    objPos tempPos;

    int candidX;
    int candidY;

    int candidSuperFood;
    int superFoodQuantity = 0;

    bool generateFood;
    srand((unsigned int)time(NULL));

    while (foodBucket->getSize() != 5)
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
        if (generateFood)
        {

            candidSuperFood = rand() % 2 + 1;
            if (candidSuperFood == 1 && superFoodQuantity < 2)
            {
                foodPos.setObjPos(candidX, candidY, '+');
                superFoodQuantity++;
            }
            else if (candidSuperFood == 2 && superFoodQuantity < 2)
            {
                foodPos.setObjPos(candidX, candidY, '-');
                superFoodQuantity++;
            }
            else
            {
                foodPos.setObjPos(candidX, candidY, '*');
            }

            foodBucket->insertHead(foodPos);
        }
        else
        {
            continue;
        }
    }
}

objPosArrayList *GameMechs::getFoodBucket()
{
    return foodBucket;
}

void GameMechs::clearFoodBucket()
{
    while (foodBucket->getSize() != 0)
    {
        foodBucket->removeTail();
    }
}

