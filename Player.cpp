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

    //check to see if the user has started playing the game
    if (myDir != STOP)
    {
        //check for collision with food if the player has not lost the game yet through self-collision
        if (checkSelfCollision(tempPos) == false)
        {
            //iterate through the food bucket array list
            for (int l = 0; l <= tempFoodBucket->getSize(); l++)
            {
                //  update the tempFoodPos object to hold the coordinate value at indiex l
                //  of the food bucket array list
                tempFoodBucket->getElement(tempFoodPos, l);
                
                //  check for player-food collision
                if (tempPos.x == tempFoodPos.x && tempPos.y == tempFoodPos.y)
                {
                  
                    //collision with superfood type 1
                    if (tempFoodPos.symbol == '+')
                    {
                        //increase player score by 10
                        mainGameMechsRef->incrementScoreTwo(10);
                    }
                    
                    //collision with superfood type 2
                    else if (tempFoodPos.symbol == '-')
                    {
                        //only apply an effect if the player body is 5 units or greater 
                        if (playerPosList->getSize() > 5)
                        {
                            
                            //invoke application of collecting a type 2 super food
                            //decrease player score by 5
                            collectSuperFoodType2();
                            mainGameMechsRef->incrementScoreTwo(-5);
                        }
                    }

                    //collision with normal food type
                    else
                    {
                        
                        //increase score and insert to the head
                        mainGameMechsRef->incrementScore();
                        playerPosList->insertHead(tempPos);
                    }

                    //clear the food bucket to make space for new generation
                    mainGameMechsRef->clearFoodBucket();

                    //generate a new food bucket
                    mainGameMechsRef->generateFood(playerPosList);

                    //update food collection status
                    collected = true;
                    break;
                }
            }

            //if player-food collision has not occured
            if (collected == false)
            {
                //insert head AND remove tail
                playerPosList->insertHead(tempPos);
                playerPosList->removeTail();
            }
        }
    }
}

bool Player::checkSelfCollision(objPos headPos)
{
    //iterate through player body array list
    for (int i = 0; i < playerPosList->getSize(); i++)
    {
        //declare object to hold current position of the player body array list
        objPos tempPos;

        //set the temporary object to hold the head position of the player body array list
        playerPosList->getElement(tempPos, i);

        //check if the temporary object collides with any other part of the player body
        if (headPos.x == tempPos.x && headPos.y == tempPos.y)
        {
            //update lose flag
            mainGameMechsRef->setLoseFlag();
            return true;
            break;
        }
    }
    return false;
}

//implementation of collecting super food type 2
void Player::collectSuperFoodType2()
{
    //remove the tail 5 times to simulate decreasing size by a factor of 5
    for(int i = 0; i < 5; i++)
        {
            playerPosList->removeTail();
        }
}
