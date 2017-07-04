#include "myMap.h"

myMap::myMap():
    underMapForinit{
{},//第0行，因为数组从零开始，所以第0行和第0列都是0
   // water 0 , house 1 , ground 2 , tree 3 ,bridge 4
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,4,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2},
{0,2,2,2,2,0,2,2,2,2} },
    aboveMapForinit{
{},
        // player1 5 , player2 6 , wood 7 , air 8 , bubble 9 , shoe 10 , drug 11
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,8,8,8},
{0,8,8,8,8,8,8,11,10,9},
{0,8,8,8,8,8,8,8,8,8} }//*/

{
    intToBlock();

}

void myMap::intToBlock()
{
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            int tempu=underMapForinit[i][j],tempa=aboveMapForinit[i][j];
            content[i][j].setUnder(uArray[tempu]);
            content[i][j].addAbove(aArray[tempa]);
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
