#include "myMap.h"

myMap::myMap()
{

}

void myMap::moveAToB(int x1,int y1,int x2,int y2)
{
    blockAt(x2,y2).addAbove(blockAt(x1,y1).getAbove());
    blockAt(x1,y1).destroyAbove();
}
//缺少检测

void myMap::hideAToB(int x1,int y1,int x2,int y2)
{
    blockAt(x2,y2).addAbove(blockAt(x1,y1).getAbove());
    blockAt(x1,y1).destroyAbove();
}
//缺少检测
