#include "board.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QDebug>

board::board(QWidget* parent):p1(),p2(),QFrame(parent)
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
    qDebug()<<"angry"<<endl;
    QPainter painter(this);
    painter.translate(20,100);
    QPixmap pground(50,50);//added
    bool flag=pground.load(":/image/images/ground.png");
    qDebug()<<flag<<endl;
    painter.drawPixmap(0,0,900,900,pground);
    countMapForDraw();
    for (int i=1;i<10;i++)
    {
        for (int j=1;j<10;j++)
        {
            //qDebug()<<i<<" "<<j<<endl;
            substance judge=mapForDraw[i][j];
            texture image;
            if (judge.us==tree&&judge.us==water&&judge.us==house)
            {
                underSubstance tmp=judge.us;
                switch(tmp)
                {
                case tree:
                {
                    image=t_tree;
                    break;
                }
                case water:
                {
                    image=t_nothing;
                    break;
                }
                case house:
                    image=t_house;
                    break;
                case ground:
                    QPixmap pix(50,50);
                    pix.load(":/image/images/player1.png");
                    painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                    break;
                }
            }
            else
            {
                aboveSubstance tmp=judge.as;
                switch(tmp)
                {
                case sBomb:
                {
                    image=t_bomb;
                }
                case arrowDown:
                case arrowLeft:
                case arrowRight:
                case arrowUp:
                {
                    image=t_flame;
                }
                case player1:
                {
                    image=t_player1;
                }
                case player2:
                {
                    image=t_player2;
                }
                case wood:
                {
                    image=t_wood;
                }
                case air:
                {
                    image=t_nothing;
                }
                }
            }
            switch(image)
            {
            case t_player1:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/player1.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_player2:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/player2.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_tree:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/tree.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_wood:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/wood.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_bomb:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/bomb.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_house:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/house.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_flame:
            {
                QPixmap pix(50,50);
                pix.load(":/image/images/flame.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
            case t_nothing:
                QPixmap pix(50,50);
                pix.load(":/image/images/flame.png");
                painter.drawPixmap(100*i-100,100*j-120,100,120,pix);
                break;
            }
        }
    }
    qDebug()<<"be"<<endl;
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
