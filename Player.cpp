#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // initialize player coordinates
    objPos tempPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    //  Need to recieve some input to process
    //  --> use gameMechs class to do this

    switch (mainGameMechsRef->getInput())
    {
    case 27:
        mainGameMechsRef->setExitTrue();
        break;
    case 'w':
        if (myDir != DOWN)
        {
            myDir = UP;
        }
        break;
    case 'a':
        if (myDir != RIGHT)
        {

            myDir = LEFT;
        }
        break;
    case 's':
        if (myDir != UP)
        {

            myDir = DOWN;
        }
        break;
    case 'd':
        if (myDir != LEFT)
        {

            myDir = RIGHT;
        }
        break;
    default:
        break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos tempPos;
    objPos tempFoodPos;
    playerPosList->getHeadElement(tempPos);
    if (myDir == DOWN)
    {
        if (tempPos.y == mainGameMechsRef->getBoardSizeY() - 1)
        {
            tempPos.y = 1;
        }
        tempPos.y++;
    }
    else if (myDir == UP)
    {

        if (tempPos.y == 2)
        {
            tempPos.y = mainGameMechsRef->getBoardSizeY();
        }
        tempPos.y--;
    }
    else if (myDir == LEFT)
    {
        if (tempPos.x == 2)
        {
            tempPos.x = mainGameMechsRef->getBoardSizeX();
        }
        tempPos.x--;
    }
    else if (myDir == RIGHT)
    {
        if (tempPos.x == mainGameMechsRef->getBoardSizeX() - 1)
        {
            tempPos.x = 1;
        }
        tempPos.x++;
    }
    mainGameMechsRef->getFoodPos(tempFoodPos);
    if (tempPos.x == tempFoodPos.x && tempPos.y == tempFoodPos.y)
    {
        playerPosList->insertHead(tempPos);
        mainGameMechsRef->generateFood(getPlayerPos());
    }
    else
    {
        playerPosList->insertHead(tempPos);
        playerPosList->removeTail();
    }


}
