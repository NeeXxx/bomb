#include "bomb.h"

void bomb::explode()
{

}

bool bomb::canExplode(int time)
{
    return time-setTime>=explodeTime;
}
