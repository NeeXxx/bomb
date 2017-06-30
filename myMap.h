#ifndef MYMAP_H
#define MYMAP_H

#include "block.h"

class myMap
{
    block content[10][10];
public:
    myMap();
    block& blockAt(int x,int y) { return content[x][y]; }
    void moveAToB(int x1,int y1,int x2,int y2);
    void hideAToB(int x1,int y1,int x2,int y2);
};

#endif // MYMAP_H
