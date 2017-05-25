#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trains.push_back(new Trem(1,20,180));
    trains.push_back(new Trem(2,220,30));
    trains.push_back(new Trem(3,420,30));
    trains.push_back(new Trem(4,620,180));
    trains.push_back(new Trem(5,420,330));
    trains.push_back(new Trem(6,220,330));
    trains.push_back(new Trem(7,220,180));

    trains[6]->setVelocidade(100);
    
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

