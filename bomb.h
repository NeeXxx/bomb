#ifndef BOMB_H
#define BOMB_H


class bomb
{
public:
    bomb(int tx,int ty,int tp,int tst):x(tx),y(ty),power(tp),setTime(tst) {}
    int getPower() const { return power; }
    void explode();
    bool canExplode(int);
    int getX() { return x; }
    int getY() { return y; }

private:
    int x,y;
    int power;
    int setTime;
    const int explodeTime=30;
};

#endif // BOMB_H
