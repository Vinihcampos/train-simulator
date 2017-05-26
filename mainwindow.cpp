#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    semaphores.push_back(new Semaforo(1234,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1235,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1236,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1237,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1238,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1239,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1240,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1241,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1242,1,IPC_CREAT|0600));
    semaphores.push_back(new Semaforo(1243,1,IPC_CREAT|0600));

    trains.push_back(new Trem(1,20,180,semaphores));
    trains.push_back(new Trem(2,220,30,semaphores));
    trains.push_back(new Trem(3,420,30,semaphores));
    trains.push_back(new Trem(4,620,180,semaphores));
    trains.push_back(new Trem(5,420,330,semaphores));
    trains.push_back(new Trem(6,220,330,semaphores));
    trains.push_back(new Trem(7,220,180,semaphores));

    trains[0]->setVelocidade(100);
    trains[1]->setVelocidade(50);
    trains[2]->setVelocidade(400);
    trains[6]->setVelocidade(70);
    trains[5]->setVelocidade(100);
    
    connect(trains[0],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[1],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[2],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[3],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[4],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[5],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trains[6],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    
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
    for(int i = 0; i < semaphores.size(); ++i){
        delete semaphores[i];
    }
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

