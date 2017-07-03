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

protected:
    void paintEvent(QPaintEvent*);
};

#endif // MAINWINDOW_H
