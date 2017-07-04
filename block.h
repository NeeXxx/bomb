#ifndef BLOCK_H
#define BLOCK_H

#include "substances.h"

class block
{
    under u;
    above a;
    above middle; //用来表示人和炸弹在同一块的情况
    //friend void myMap::intToBlock();
public:
    block(under tu,above ta):u(tu),a(ta),middle(aAir) {}
    block(under tu):u(tu),a(aAir),middle(aAir) {}
    block():u(uWater),a(aAir),middle(aAir) {}

    void destroyAbove();
    void addAbove(above ta);
    above getAbove() { return a; }

    void setUnder(under tu);

    bool inable();
    bool pushable();
    bool hidable();
    bool haveAbove();

    substance appearance(); //画图必须调用appearance

    bool haveBomb() { return middle==aBomb; }
    void addBomb() { middle=aBomb; }
    void removeMiddle() { middle=aAir; }
};

#endif // BLOCK_H
