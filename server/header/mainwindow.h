#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include <QMainWindow>
#include <vector>
#include <thread>

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
    void interpret_client(char * message);

public slots:
    void updateInterface(int,int,int);
    void updateInterface(int,int);
    void updateInterface(int,double,double,double,double);
    void updateInterface();

private:
    Ui::MainWindow *ui;
    vector<Trem*> trains;
    vector<Semaforo*> semaphores;

};

#endif // MAINWINDOW_H
