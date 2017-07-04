#include "board.h"

bool board::tryMoveUp(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x-1,y);
    if(flag) p.move(-1,0);
    return flag;
}

bool board::tryMoveDown(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x+1,y);
    if(flag) p.move(1,0);
    return flag;
}

bool board::tryMoveLeft(player& p)
{
    int x=p.getX(),y=p.getY();
    qDebug()<<x<<" "<<y<<endl;
    bool flag=tryMove(x,y,x,y-1);
    if(flag) p.move(0,-1);
    return flag;
}

bool board::tryMoveRight(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x,y+1);
    if(flag) p.move(0,1);
    return flag;
}

#define ANGRY(x) qDebug()<<#x"angry!"<<endl;

bool board::tryMove(int x1,int y1,int x2,int y2) //from 1 to 2
{
    block& target=m.blockAt(x2,y2);
    qDebug()<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    if(target.inable())
    {
        ANGRY(1)
        if(target.hidable())
            return tryInToHide(x1,y1,x2,y2);
        else
        {
            ANGRY(2)
            return trySimpleMove(x1,y1,x2,y2);
        }
    }
    else
    {
        if(target.pushable())
            return tryPush(x1,y1,x2,y2);
        else
        {
            //ANGRY(!)
            return false;
        }
    }
}
//bug?

bool board::trySimpleMove(int x1,int y1,int x2,int y2)
{
    m.moveAToB(x1,y1,x2,y2);
    return true;
}

bool board::tryPush(int x1,int y1,int x2,int y2)
{
    block& target1=m.blockAt(x2,y2);
    int x3=x2+x2-x1,y3=y2+y2-y1;
    block& target2=m.blockAt(x3,y3);

    if(target2.inable())
    {
        if(target1.hidable())
            return tryInToHide(x1,y1,x2,y2);
        else
            return trySimpleMove(x1,y1,x2,y2);

        if(target2.hidable())
            return tryInToHide(x2,y2,x3,y3);
        else
            return trySimpleMove(x2,y2,x3,y3);
    }
    else
        return false;
}

bool board::tryInToHide(int x1,int y1,int x2,int y2)
{
    m.moveAToB(x1,y1,x2,y2);
    return true;
}
