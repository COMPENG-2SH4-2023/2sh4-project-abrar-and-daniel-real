#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}
//destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList == sizeArray)
    {
            return; //do nothing if the list is full
    }
    for (int i = sizeList; i > 0; i--)
    {
        //move indexes down by
        aList[i].setObjPos(aList[i - 1]);
    }
    aList[0].setObjPos(thisPos);   //insert @ sign at the start
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList == sizeArray)
    {
        return;  //do nothing if full
    }
    //add to end of the list and increase the size by one
    aList[sizeList].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::removeHead()
{
    //shift all elements up an index
    for (int i = 0; i < sizeList; i++)
    {
        aList[i].setObjPos(aList[i + 1]);
    }
    //decrease the size of the list
    sizeList--;
}

void objPosArrayList::removeTail()
{
    //remove last element and delete last index
    aList[sizeList - 1].setObjPos(aList[sizeList]);
    sizeList --;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}

