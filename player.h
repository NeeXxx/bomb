#ifndef PLAYER_H
#define PLAYER_H

#include <QDebug>


class player
{
public:
    player();
    player(int,int);

    int getSpeed() const { return speed; }
    void setSpeed(int t) { speed=t; }
    int getBombPower() const {return bombPower; }
    void setBombPower(int t) { bombPower=t; }
    int getX() { return x; }
    int getY() { return y; }

    void move(int dx,int dy) { qDebug()<<"alarm!"<<endl; x+=dx; y+=dy; }

private:
    int speed;
    int bombPower;
    int bombNum; //总共能放多少个炸弹
    int bombLeft; //还能放多少个炸弹
    int x,y;

};

#endif // PLAYER_H
