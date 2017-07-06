#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    board b;

private:
    Ui::MainWindow *ui;
    QBasicTimer timer;

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent *event);
private slots:
    void on_actionRestart_triggered();
};

#endif // MAINWINDOW_H
