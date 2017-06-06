#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include "header/system_train.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <QFileInfo>

QStandardItemModel * model;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    for(int i = 0, j = 1234; i < 10; ++i, ++j){
        System::semaphores.push_back(new Semaforo(j,1,IPC_CREAT|0600));
    }

    System::logS = new Semaforo(1245, 1, IPC_CREAT|0600);
    System::log_file = (QFileInfo(".").absolutePath()).toStdString() + "/server/logs/log_" + System::currentDateTime() + ".txt";
    trains.push_back(new Trem(1,20,180));
    trains.push_back(new Trem(2,220,30));
    trains.push_back(new Trem(3,420,30));
    trains.push_back(new Trem(4,620,180));
    trains.push_back(new Trem(5,420,330));
    trains.push_back(new Trem(6,220,330));
    trains.push_back(new Trem(7,220,180));

    /*trains[6]->setVelocidade(20);
    trains[5]->setVelocidade(20);
    trains[4]->setVelocidade(30);
    trains[3]->setVelocidade(40);
    trains[2]->setVelocidade(50);
    trains[1]->setVelocidade(60);
    trains[0]->setVelocidade(1000);*/

    for(unsigned int i = 0; i < trains.size(); ++i){
        // Update lap informations
        connect(trains[i],SIGNAL(updateGUI(int,double,double,double,double)),SLOT(updateInterface(int,double,double,double,double)));
        // Update train position
        connect(trains[i],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
        // Update semaphores states
        connect(trains[i],SIGNAL(updateGUI(int,int)),SLOT(updateInterface(int,int)));
        // Update log
        connect(trains[i],SIGNAL(updateGUI()),SLOT(updateInterface()));
        // Train start
        trains[i]->start();
    }

}

MainWindow::~MainWindow()
{
    ::close(System::socket_id);
    delete ui;
    System::clear();
}

void MainWindow::interpret_client(char * message) {
    std::string s {message};
    std::stringstream ss {s};
    std::string op;
    ss >> op;
    if (op == "INFO") {
        std::string tosend;
        std::string w;
        ss >> w;
        if (w == "E") {
            for (auto t : trains)
                tosend += t->getEnable() ? "ON " : "OFF ";
            std::cout << "Sending informations about enabled: " << tosend << std::endl;
        } else if (w == "V") {
            for (auto t : trains)
                tosend += std::to_string((int) (10.0/(t->getVelocidade()/1000.0))) + " ";
            std::cout << "Sending informations about velocity: " << tosend << std::endl;
        }
        tosend += "\0";
        send(System::client_id,(char *) tosend.c_str(), strlen(tosend.c_str()),0);
    } else if (op == "ON") {
        std::string t;
        ss >> t;
        // Turn off all
        if (t == "A") {
            for (auto t : trains)
                t->setEnable(true);
        } else {
            int ti = stoi(t);
            trains[ti-1]->setEnable(true);
        }
    } else if (op == "OFF") {
        std::string t;
        ss >> t;
        // Turn off all
        if (t == "A") {
            for (auto t : trains)
                t->setEnable(false);
        } else {
            int ti = stoi(t);
            trains[ti-1]->setEnable(false);
        }
    } else if (op == "SPEED") {
        std::string id;
        int vel;
        ss >> id >> vel;
        trains[stoi(id)]->setVelocidade(vel);
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

void MainWindow::updateInterface(int id, double mean, double sd, double lastValue, double currLap){
    switch(id){
        case 1:
            ui->labelLapTrain1CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain1AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain1SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain1LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 2:
            ui->labelLapTrain2CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain2AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain2SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain2LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 3:
            ui->labelLapTrain3CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain3AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain3SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain3LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 4:
            ui->labelLapTrain4CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain4AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain4SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain4LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 5:
            ui->labelLapTrain5CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain5AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain5SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain5LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 6:
            ui->labelLapTrain6CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain6AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain6SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain6LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        case 7:
            ui->labelLapTrain7CL->setText(QString::number(floor(currLap * 100) / 100) + "s");
            ui->labelLapTrain7AT->setText(QString::number(floor(mean * 100) / 100) + "s");
            ui->labelLapTrain7SD->setText(QString::number(floor(sd * 100) / 100));
            ui->labelLapTrain7LP->setText(QString::number(floor(lastValue * 100) / 100) + "s");
            break;
        default:
            break;
    }
}

void MainWindow::updateInterface(){
    ui->listLog->clear();
    std::cout << System::logs.size() << std::endl;
    for(int i = System::logs.size() - 1; i >= 0; --i){
        ui->listLog->addItem(QString::fromStdString(System::logs[i]));
    }

}
