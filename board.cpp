#include "board.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <map>
#include <string>
using namespace  std;

board::board(QWidget* parent):QFrame(parent),p1(),p2()
{
    //merge
    //qDebug()<<"angry"<<endl;
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    cnt=0;
    timer.start(100,this);
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

bool board::tryMoveUp(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x,y-1);
    if(flag) p.move(0,-1);
    return flag;
}

bool board::tryMoveDown(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x,y+1);
    if(flag) p.move(0,1);
    return flag;
}

bool board::tryMoveLeft(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x-1,y);
    if(flag) p.move(-1,0);
    return flag;
}

bool board::tryMoveRight(player& p)
{
    int x=p.getX(),y=p.getY();
    bool flag=tryMove(x,y,x+1,y);
    if(flag) p.move(1,0);
    return flag;
}

bool board::tryMove(int x1,int y1,int x2,int y2) //from 1 to 2
{
    block& target=m.blockAt(x2,y2);
    if(target.inable())
    {
        if(target.hidable())
            return tryInToHide(x1,y1,x2,y2);
        else
            return trySimpleMove(x1,y1,x2,y2);
    }
    else
    {
        if(target.pushable())
            return tryPush(x1,y1,x2,y2);
        else return false;
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

void board::paintEvent(QPaintEvent*)
{
    //绘制地图底板
    QPainter painter(this);
    painter.translate(20,100);
    QPixmap tground;
    tground.load(":/image/images/ground.png");
    painter.drawPixmap(0,0,900,900,tground);
    //绘制前的定义
    std::map<aboveSubstance,QString> aM;
    std::map<underSubstance,QString> uM;
    aM[player1]="player1.png";
    aM[player2]="player2.png";
    aM[wood]="wood.png";
    aM[sBomb]="bomb.png";
    aM[arrowDown]=aM[arrowLeft]=aM[arrowRight]=aM[arrowUp]="flame.png";
    uM[house]="hosue.png";
    uM[tree]="tree.png";
    uM[water]=uM[ground]=uM[bridge]="blank.png";
    QString name, full_name;
    //绘制每格元素
    countMapForDraw();
    QPixmap pix;
    for (int i=1;i<10;i++)
    {
        for (int j=1;j<10;j++)
        {
            substance judge=mapForDraw[i][j];
            if (judge.as!=air)
            {
                name=aM[judge.as];
            }
            else
            {
                name=uM[judge.us];
            }
            full_name=":/image/images/"+name;
            pix.load(full_name);
            painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
        }
    }
}

void board::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    //p1:
    case Qt::Key_W:
        tryMoveUp(p1);
        break;
    case Qt::Key_S:
        tryMoveDown(p1);
        break;
    case Qt::Key_A:
        tryMoveLeft(p1);
        break;
    case Qt::Key_D:
        tryMoveRight(p1);
        break;
    case Qt::Key_F:
        setBomb(p1);
        break;

    //p2:
    case Qt::Key_Up:
        tryMoveUp(p2);
        break;
    case Qt::Key_Down:
        tryMoveDown(p2);
        break;
    case Qt::Key_Left:
        tryMoveLeft(p2);
        break;
    case Qt::Key_Right:
        tryMoveRight(p2);
        break;
    case Qt::Key_Shift:
        setBomb(p2);
        break;
    }
}

void board::timerEvent(QTimerEvent* event)
{

    if(event->timerId()==timer.timerId())
    {
        cnt++;
        qDebug()<<"naive"<<cnt<<endl;
        repaint();
        while(!bombQueue.empty() && bombQueue.front().canExplode(cnt))
        {
            bombQueue.front().explode();
            bombQueue.pop();
        }
    }
}
