#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

private:
    objPos foodPos;
    objPosArrayList *foodBucket;
    char input;
    bool exitFlag;
    bool loseFlag;
    int score;

    int boardSizeX;
    int boardSizeY;

public:
    GameMechs();                       // done
    GameMechs(int boardX, int boardY); // done

    ~GameMechs();

    objPosArrayList *getFoodBucket();

    void clearFoodBucket();

    bool getExitFlagStatus();       // done
    bool getLoseFlagStatus();       // done
    void setExitTrue();             // done
    void setLoseFlag();             // done
    char getInput();                // done
    void setInput(char this_input); // done
    void clearInput();              // done
    void incrementScore();          // done
    void incrementScoreTwo(int x);
    int getBoardSizeX(); // done
    int getBoardSizeY(); // done
    int getScore();      // dome

    void generateFood(objPosArrayList *blockOff);
    void getFoodPos(objPos &returnPos);
};

#endif