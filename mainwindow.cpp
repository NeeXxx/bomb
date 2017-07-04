#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),b(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(&b);
    resize(1200,900);
    timer.start(100,this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    b.keyPressEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //qDebug()<<"angry!"<<endl;
    //绘制地图底板
    QPainter painter(this);
    painter.translate(20,100);
    QPixmap tground;
    tground.load(":/image/images/ground.png");
    painter.drawPixmap(0,0,720,720,tground);
    //绘制前的定义
    std::map<aboveSubstance,QString> aM;
    std::map<underSubstance,QString> uM;
    aM[player1]="player1.png";
    aM[player2]="player2.png";
    aM[wood]="wood.png";
    aM[sBomb]="bomb.png";
    aM[bubble]="bubble.gif";
    aM[shoe]="shoe.gif";
    aM[drug]="drug.gif";
    aM[arrowDown]=aM[arrowLeft]=aM[arrowRight]=aM[arrowUp]="flame.png";
    uM[house]="house.png";
    uM[tree]="tree.png";
    uM[water]=uM[ground]=uM[bridge]="blank.png";
    QString name, full_name;
    //绘制每格元素
    b.countMapForDraw();
    QPixmap pix;
    for (int i=1;i<10;i++)
    {
        for (int j=1;j<10;j++)
        {
            substance judge=b.mapForDraw[j][i];
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
            painter.drawPixmap(80*i-80,80*j-96,80,96,pix);
        }
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    //if(event->timerId()==timer.timerId())
        //update();
}
