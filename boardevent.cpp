#include "board.h"


/*
void board::paintEvent(QPaintEvent*)
{
    qDebug()<<"angry!"<<endl;
    //绘制地图底板
    QPainter painter(this);
    //painter.translate(20,100);
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
//*/

void board::keyPressEvent(QKeyEvent* event)
{
    bool flag;
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

    //*p2:
    case Qt::Key_Up:
        flag=tryMoveUp(p2);
        qDebug()<<flag<<endl;
        break;
    case Qt::Key_Down:
        flag=tryMoveDown(p2);
        qDebug()<<flag<<endl;
        break;
    case Qt::Key_Left:
        flag=tryMoveLeft(p2);
        qDebug()<<flag<<endl;
        break;
    case Qt::Key_Right:
        flag=tryMoveRight(p2);
        qDebug()<<flag<<endl;
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
        //qDebug()<<p2->getX()<<" "<<p2->getY()<<endl;
        //qDebug()<<"naive"<<cnt<<endl;
        //repaint();
        while(!bombQueue.empty() && bombQueue.front().canExplode(cnt))
        {
            bombQueue.front().explode();
            bombQueue.pop();
        }
    }
}
