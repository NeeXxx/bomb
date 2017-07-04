#include "player.h"

player::player()
{
    x=1,y=1;
    bombPower=1;
    bombNum=1;
    bombLeft=1;
    speed=1;
}

player::player(int tx,int ty)
{
    x=tx,y=ty;
    bombPower=1;
    bombNum=1;
    bombLeft=1;
    speed=1;
}
