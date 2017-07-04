#include "board.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <map>
#include <string>
using namespace  std;

board::board(QWidget* parent):QFrame(parent),p1(1,1),p2(3,8)
{
    //merge
    //qDebug()<<"angry"<<endl;
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    cnt=0;
    timer.start(100,this);
    resize(1000,1000);
    initPlayer1();
    initPlayer2();
    qDebug()<<p2.getX()<<" "<<p2.getY()<<endl;
}

void board::initPlayer1()
{
    int x=p1.getX(),y=p1.getY();
    m.blockAt(x,y).addAbove(aPlayer1);
}

void board::initPlayer2()
{
    int x=p2.getX(),y=p2.getY();
    m.blockAt(x,y).addAbove(aPlayer2);
}

void board::setBomb(player p)
{
    int x=p.getX(),y=p.getY();
    m.blockAt(x,y).addBomb();
    bombQueue.push(bomb(x,y,p.getBombPower(),cnt));
}//绘图是个问题

void board::explode(bomb b)
{
    int x=b.getX(),y=b.getY();
    m.blockAt(x,y).destroyAbove();//还不完善，人还在上面怎么办
}



void board::countMapForDraw()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
        {
            block& temp=m.blockAt(i,j);
            if(temp.haveBomb() && temp.getAbove()==aAir)
            {
                temp.removeMiddle();
                temp.addAbove(aBomb);
            }
            mapForDraw[i][j]=temp.appearance();
        }
}

bool board::inMap(int x,int y)
{
    return x>=1 && x<=9 && y>=1 && y<=9;
}
