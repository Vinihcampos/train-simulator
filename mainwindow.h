#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include <QMainWindow>
#include <vector>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterface(int,int,int);

private:
    Ui::MainWindow *ui;
    vector<Trem*> trains;
    vector<Semaforo*> semaphores;
};

#endif // MAINWINDOW_H
