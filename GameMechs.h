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
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs(); //done
        GameMechs(int boardX, int boardY); //done

        bool getExitFlagStatus();  //done
        bool getLoseFlagStatus();    //done
        void setExitTrue();         //done
        void setLoseFlag();         //done
        char getInput();            //done
        void setInput(char this_input); //done
        void clearInput();          //done
        void incrementScore();      //done

        int getBoardSizeX();        //done
        int getBoardSizeY();        //done
        int getScore();             //dome



};

#endif