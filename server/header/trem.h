#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "semaforo.h"

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);
    bool getEnable();
    int getVelocidade();

signals:
    void updateGUI(int,int,int);
    void updateGUI(int,int);
    void updateGUI(int,double,double,double,double);
    void updateGUI();

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade = 0;
   bool enable = false;
   int laps;
   double currLap;
   double totalTime;
   double lastLap;
   int xStart,yStart;
   double var;
};

#endif // TREM_H



