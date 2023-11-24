#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // initialize player coordinates
    playerPos.setObjPos(10, 5, '@');
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    //  Need to recieve some input to process
    //  --> use gameMechs class to do this

    char input = mainGameMechsRef->getInput();

    switch (input)
    {
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

    // 0 1 2 3 4 5 6 7 8 9
    if (myDir == DOWN)
    {
        if (playerPos.y == mainGameMechsRef->getBoardSizeY() - 1)
        {
            playerPos.y == 1;
        }
        playerPos.y--;
    }
    else if (myDir == UP)
    {
        if (playerPos.y == 12 % mainGameMechsRef->getBoardSizeY())
        {
            playerPos.y == 10;
        }
        playerPos.y++;
    }
    else if (myDir == LEFT)
    {
        if (playerPos.x == 22 % mainGameMechsRef->getBoardSizeX())
        {
            playerPos.x == 20;
        }
        playerPos.x--;
    }
    else if (myDir == RIGHT)
    {
        if (playerPos.x == mainGameMechsRef->getBoardSizeX() - 1)
        {
            playerPos.x == 1;
        }
        playerPos.x++;
    }
}
