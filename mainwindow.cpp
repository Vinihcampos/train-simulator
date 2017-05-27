#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system_train.h"
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    System::semaphores.push_back(new Semaforo(1234,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1235,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1236,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1237,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1238,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1239,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1240,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1241,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1242,1,IPC_CREAT|0600));
    System::semaphores.push_back(new Semaforo(1243,1,IPC_CREAT|0600));

    trains.push_back(new Trem(1,20,180));
    trains.push_back(new Trem(2,220,30));
    trains.push_back(new Trem(3,420,30));
    trains.push_back(new Trem(4,620,180));
    trains.push_back(new Trem(5,420,330));
    trains.push_back(new Trem(6,220,330));
    trains.push_back(new Trem(7,220,180));

    //trains[5]->setVelocidade(20);
    //trains[4]->setVelocidade(30);
    //trains[3]->setVelocidade(40);
    //trains[2]->setVelocidade(50);
    //trains[1]->setVelocidade(60);
    //trains[0]->setVelocidade(70);
    
    connect(trains[0],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[1],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[2],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[3],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[4],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[5],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[6],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[0],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[1],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[2],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[3],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[4],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[5],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    connect(trains[6],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
    
    trains[0]->start();
    trains[1]->start();
    trains[2]->start();
    trains[3]->start();
    trains[4]->start();
    trains[5]->start();
    trains[6]->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    System::clear();
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrain1->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrain2->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrain3->setGeometry(x,y,20,20);
            break;
        case 4:
            ui->labelTrain4->setGeometry(x,y,20,20);
            break;
        case 5:
            ui->labelTrain5->setGeometry(x,y,20,20);
            break;
        case 6:
            ui->labelTrain6->setGeometry(x,y,20,20);
            break;
        case 7:
            ui->labelTrain7->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}

void MainWindow::updateInterface(int id, int state)
{   
    QString color = "background-color:green;border-radius:14px;color:white;";
    if(!state) color = "background-color:red;border-radius:14px;color:white;";

    switch(id){
        case 0:
            ui->labelSemaphore1->setStyleSheet(color);
            break;
        case 1:
            ui->labelSemaphore2->setStyleSheet(color);
            break;
        case 2:
            ui->labelSemaphore3->setStyleSheet(color);
            break;
        case 3:
            ui->labelSemaphore4->setStyleSheet(color);
            break;
        case 4:
            ui->labelSemaphore5->setStyleSheet(color);
            break;
        case 5:
            ui->labelSemaphore6->setStyleSheet(color);
            break;
        case 6:
            ui->labelSemaphore7->setStyleSheet(color);
            break;
        case 7:
            ui->labelSemaphore8->setStyleSheet(color);
            break;
        case 8:
            ui->labelSemaphore9->setStyleSheet(color);
            break;
        case 9:
            ui->labelSemaphore10->setStyleSheet(color);
            break;
        default:
            break;
    }
}

