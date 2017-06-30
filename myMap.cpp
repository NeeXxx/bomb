#include "myMap.h"

myMap::myMap()
{

}

void myMap::intToBlock()
{
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            int temp=mapForinit[i][j];
            if(temp>=0 && temp<=4)
            {
                content[i][j].u=uArray[temp];
                content[i][j].a=aAir;
            }
            else
            {
                int tempa=temp%5;
                content[i][j].a=aArray[]
            }
        }
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
