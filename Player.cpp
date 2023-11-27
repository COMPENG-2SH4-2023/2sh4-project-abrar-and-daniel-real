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
    objPosArrayList *tempFoodBucket = mainGameMechsRef->getFoodBucket();
    bool collected = false;

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
    if (myDir != STOP)
    {
        if (checkSelfCollision(tempPos) == false)
        {
            for (int l = 0; l <= tempFoodBucket->getSize(); l++)
            {
                tempFoodBucket->getElement(tempFoodPos, l);
                // this line of code guarantees that we are on top of some random food obj
                // who's pos. we do not know..........
                if (tempPos.x == tempFoodPos.x && tempPos.y == tempFoodPos.y)
                {
                    // here, I will check to see what the collided pos. actually is
                    if (tempFoodPos.symbol == '+')
                    {
                        // lets say + will increase the player score by 10 without affecting the player snake body length
                        mainGameMechsRef->incrementScoreTwo(10);
                    }
                    else if (tempFoodPos.symbol == '-')
                    {
                        // lets pretend that this symbol is one that you do not want to collect
                        // hence, it should have a negatice consequence should you collect it
                        // for ex.... let's do: it decreases your snake length.
                        // problem! --> we cant't decrease the snake length if the '-' superfood is the first food
                        //  we collect on the board, because we start with a length of 1...... a length of 0
                        //  is not possible.....
                        //  so, if we collect a '-' with a length of 1, we will simply regenerate the board without doing anythigm.
                        // lets try!
                        if (playerPosList->getSize() > 5)
                        {

                            collectSuperFoodType2();
                            mainGameMechsRef->incrementScoreTwo(-5);
                        }
                    }
                    else
                    {

                        mainGameMechsRef->incrementScore();
                        playerPosList->insertHead(tempPos);
                    }
                    mainGameMechsRef->clearFoodBucket();
                    mainGameMechsRef->generateFood(playerPosList);
                    collected = true;
                    break;
                }
            }
            if (collected == false)
            {
                playerPosList->insertHead(tempPos);
                playerPosList->removeTail();
            }
        }
    }
}

bool Player::checkSelfCollision(objPos headPos)
{
    for (int i = 0; i < playerPosList->getSize(); i++)
    {
        objPos tempPos;
        playerPosList->getElement(tempPos, i);
        if (headPos.x == tempPos.x && headPos.y == tempPos.y)
        {
            mainGameMechsRef->setLoseFlag();
            return true;
            break;
        }
    }
    return false;
}

void Player::collectSuperFoodType2()
{
    while (playerPosList->getSize() != 1)
    {
        playerPosList->removeTail();
    }
}
