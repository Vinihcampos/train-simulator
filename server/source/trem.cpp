#include "header/trem.h"
#include "header/system_train.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 600;
    enable = false;
    laps = 0;
    currLap = 0;
    lastLap = 0;
    totalTime = 0;
    xStart = x;
    yStart = y;
    var = 0;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

bool Trem::getEnable() {
    return this->enable;
}

int Trem::getVelocidade() {
    return this->velocidade;
}


void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run(){
    while(true){
        string msg = "";
        switch(id){
            case 1:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 20 && y > 30) {
                        y-=10;
                    }else if (y == 30 && x < 120){
                        if(x == 100) {
                            if(System::semaphores[0]->getContador()){
                                System::semaphores[0]->P();
                                msg = "T1.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore1.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(0, System::semaphores[0]->getContador());
                                x+=10;
                            }
                        }else x+=10;
                    }else if (x == 120 && y < 330){
                        if(y == 150){ 
                            if(!System::semaphores[0]->getContador()) {
                                System::semaphores[0]->V();
                                msg = "T1.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore1.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(0, System::semaphores[0]->getContador());
                            }y += 10;                                
                        }else if(y == 210){
                            if(System::semaphores[7]->getContador()){
                                System::semaphores[7]->P();
                                msg = "T1.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore8.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(7, System::semaphores[7]->getContador());
                                y+=10;
                            }
                        }
                        else y+=10;
                    }else {
                        if(x == 100) 
                            if(!System::semaphores[7]->getContador()){ 
                                System::semaphores[7]->V();
                                msg = "T1.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore8.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(7, System::semaphores[7]->getContador());
                            }
                        x-=10;
                    }
                }
                break;
            case 2:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 120 && y > 30){
                        y-=10;
                    }else if (y == 30 && x < 320){
                        if(x == 140){ 
                            if(!System::semaphores[0]->getContador()) {
                                System::semaphores[0]->V();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore1.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(0, System::semaphores[0]->getContador());
                            }x+=10;
                        }else if(x == 300){
                            if(System::semaphores[4]->getContador()){
                                System::semaphores[4]->P();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        x+=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    x+=10;
                                }
                            }else if(!System::semaphores[4]->getContador()){
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        x+=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    x+=10;
                                }
                            }
                        }else x+=10;
                    }else if (x == 320 && y < 130){
                        y+=10;
                    }else{
                        if(x == 140) {
                            if(System::semaphores[0]->getContador()){
                                System::semaphores[0]->P();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore1.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(0, System::semaphores[0]->getContador());
                                x-=10;
                            }
                        }else if(x == 200){
                            if(!System::semaphores[3]->getContador()) {
                                System::semaphores[3]->V();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(3, System::semaphores[3]->getContador());
                            }
                            if(!System::semaphores[1]->getContador()) {
                                System::semaphores[1]->V();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(1, System::semaphores[1]->getContador());
                            }
                            if(!System::semaphores[4]->getContador()) {
                                System::semaphores[4]->V();
                                msg = "T2.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                            }
                            x-=10;
                        }else x-=10;
                    }
                }
                break;
            case 3:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 320 && y > 30){
                        y-=10;
                    }else if (y == 30 && x < 520){ 
                        if(x == 340){
                            if(!System::semaphores[3]->getContador()) {
                                System::semaphores[3]->V();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(3, System::semaphores[3]->getContador());
                            }
                            if(!System::semaphores[1]->getContador()) {
                                System::semaphores[1]->V();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(1, System::semaphores[1]->getContador());
                            }
                            if(!System::semaphores[4]->getContador()) {
                                System::semaphores[4]->V();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                            }
                            x+=10;
                        }else if(x == 500){
                            if(System::semaphores[2]->getContador()){
                                System::semaphores[2]->P();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore3.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(2, System::semaphores[2]->getContador());
                                x+=10;
                            }
                        }
                        else x+=10;
                    }else if (x == 520 && y < 130){
                        y+=10; 
                    }else{
                        if(x == 440){
                            if(System::semaphores[4]->getContador()){
                                System::semaphores[4]->P();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        x-=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    x-=10;
                                }
                            }else if(!System::semaphores[4]->getContador()){
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        x-=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    x-=10;
                                }
                            }
                        }else if(x == 500) {
                            if(!System::semaphores[2]->getContador()) {
                                System::semaphores[2]->V();
                                msg = "T3.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore3.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(2, System::semaphores[2]->getContador());
                            }
                            x-=10;
                        }else x-=10;
                    }
                }
                break;
            case 4:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 520 && y > 30){
                        if(y == 150){
                            if(System::semaphores[2]->getContador()){
                                System::semaphores[2]->P();
                                msg = "T4.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore3.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(2, System::semaphores[2]->getContador());
                                y-=10;
                            }
                        }else if(y == 210){
                            if(!System::semaphores[9]->getContador()) {
                                System::semaphores[9]->V();
                                msg = "T4.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore10.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(9, System::semaphores[9]->getContador());
                            }y-=10;
                        }
                        else y-=10;
                    }else if (y == 30 && x < 620){ 
                        if(x == 540) if(!System::semaphores[2]->getContador()) {
                            System::semaphores[2]->V();
                            msg = "T4.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore3.V()";
                            System::mtx.lock();
                            System::updateLog(msg);
                            emit updateGUI();
                            System::mtx.unlock();
                            emit updateGUI(2, System::semaphores[2]->getContador());
                        }x+=10;
                    }else if (x == 620 && y < 330){ 
                        y+=10;
                    }else{
                        if(x == 540){
                            if(System::semaphores[9]->getContador()){
                                System::semaphores[9]->P();
                                msg = "T4.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore10.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(9, System::semaphores[9]->getContador());
                                x-=10;
                            }
                        }
                        else x-=10;
                    }
                }
                break;
            case 5:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 320 && y > 230){
                        y-=10;
                    }else if (y == 230 && x < 520){
                        if(x == 440){
                            if(!System::semaphores[6]->getContador()) {
                                System::semaphores[6]->V();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(6, System::semaphores[6]->getContador());
                            }if(!System::semaphores[8]->getContador()) {
                                System::semaphores[8]->V();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(8, System::semaphores[8]->getContador());
                            }if(!System::semaphores[5]->getContador()) {
                                System::semaphores[5]->V();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                            }x+=10;
                        }else if(x == 500){
                            if(System::semaphores[9]->getContador()){
                                System::semaphores[9]->P();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore10.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(9, System::semaphores[9]->getContador());
                                x+=10;
                            }
                        }
                        else x+=10;
                    }else if (x == 520 && y < 330){
                        y+=10;
                    }else{
                        if(x == 340){
                            if(System::semaphores[5]->getContador()){
                                System::semaphores[5]->P();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        x-=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    x-=10;
                                }
                            }else if(!System::semaphores[5]->getContador()){
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        x-=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    x-=10;
                                }
                            }
                        }else if(x == 500) {
                            if(!System::semaphores[9]->getContador()) {
                                System::semaphores[9]->V();
                                msg = "T5.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore10.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(9, System::semaphores[9]->getContador());
                            }x-=10;
                        }else x-=10;
                    }
                }
                break;
            case 6:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 120 && y > 230) {
                        y-=10;
                    }else if (y == 230 && x < 320){ 
                        if(x == 140) {
                            if(!System::semaphores[7]->getContador()) {
                                System::semaphores[7]->V();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore8.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(7, System::semaphores[7]->getContador());
                            }x+=10;
                        }else if(x == 200){
                            if(System::semaphores[5]->getContador()){
                                System::semaphores[5]->P();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        x+=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    x+=10;
                                }
                            }else if(!System::semaphores[5]->getContador()){
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        x+=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    x+=10;
                                }
                            }
                        }else x+=10;
                    }else if (x == 320 && y < 330){ 
                        y+=10;
                    }else{
                        if(x == 300){
                            if(!System::semaphores[6]->getContador()){
                                System::semaphores[6]->V();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(6, System::semaphores[6]->getContador());
                            }if(!System::semaphores[8]->getContador()){
                                System::semaphores[8]->V();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(8, System::semaphores[8]->getContador());
                            }if(!System::semaphores[5]->getContador()){
                                System::semaphores[5]->V();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                            }x-=10;
                        }else if(x == 140){
                            if(System::semaphores[7]->getContador()){
                                System::semaphores[7]->P();
                                msg = "T6.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore8.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(7, System::semaphores[7]->getContador());
                                x-=10;
                            }
                        }else x-=10;
                    }
                }
                break;
            case 7:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 220 && y > 130){
                        if(y == 210){
                            if(!System::semaphores[6]->getContador()) {
                                System::semaphores[6]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(6, System::semaphores[6]->getContador());
                            }
                            if(!System::semaphores[8]->getContador()) {
                                System::semaphores[8]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(8, System::semaphores[8]->getContador());
                            }
                            if(!System::semaphores[5]->getContador()) {
                                System::semaphores[5]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                            }
                            y-=10;
                        }else if(y == 150){
                            if(System::semaphores[4]->getContador()){
                                System::semaphores[4]->P();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        y-=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    y-=10;
                                }
                            }else if(!System::semaphores[4]->getContador()){
                                if(System::semaphores[1]->getContador()){
                                    System::semaphores[1]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(1, System::semaphores[1]->getContador());
                                    if(System::semaphores[3]->getContador()){
                                        System::semaphores[3]->P();
                                        msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(3, System::semaphores[3]->getContador());
                                        y-=10;
                                    }
                                }
                                else if(!System::semaphores[1]->getContador() && System::semaphores[3]->getContador()){
                                    System::semaphores[3]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(3, System::semaphores[3]->getContador());
                                    y-=10;
                                }
                            }
                        }else y-=10;
                    }else if (y == 130 && x < 420){
                        x+=10;
                    }else if (x == 420 && y < 230){
                        if(y == 150) {
                            if(!System::semaphores[3]->getContador()) {
                                System::semaphores[3]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore4.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(3, System::semaphores[3]->getContador());
                            }
                            if(!System::semaphores[1]->getContador()) {
                                System::semaphores[1]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore2.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(1, System::semaphores[1]->getContador());
                            }
                            if(!System::semaphores[4]->getContador()) {
                                System::semaphores[4]->V();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore5.V()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(4, System::semaphores[4]->getContador());
                            }
                            y+=10;
                        }else if(y == 210){
                            if(System::semaphores[5]->getContador()){
                                System::semaphores[5]->P();
                                msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore6.P()";
                                System::mtx.lock();
                                System::updateLog(msg);
                                emit updateGUI();
                                System::mtx.unlock();
                                emit updateGUI(5, System::semaphores[5]->getContador());
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        y+=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    y+=10;
                                }
                            }else if(!System::semaphores[5]->getContador()){
                                if(System::semaphores[8]->getContador()){
                                    System::semaphores[8]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore9.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(8, System::semaphores[8]->getContador());
                                    if(System::semaphores[6]->getContador()){
                                        System::semaphores[6]->P();
                                        msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                        System::mtx.lock();
                                        System::updateLog(msg);
                                        emit updateGUI();
                                        System::mtx.unlock();
                                        emit updateGUI(6, System::semaphores[6]->getContador());
                                        y+=10;
                                    }
                                }
                                else if(!System::semaphores[8]->getContador() && System::semaphores[6]->getContador()){
                                    System::semaphores[6]->P();
                                    msg = "T7.Pos("+std::to_string(x)+","+std::to_string(y)+").semaphore7.P()";
                                    System::mtx.lock();
                                    System::updateLog(msg);
                                    emit updateGUI();
                                    System::mtx.unlock();
                                    emit updateGUI(6, System::semaphores[6]->getContador());
                                    y+=10;
                                }
                            }
                        }else y+=10;
                    }else{
                        x-=10;
                    }
                }
                break;
            default:
                break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
        
        if(this->enable){
            currLap += velocidade / 1000.0;
            if(x == xStart && y == yStart){
                ++laps;
                var =  laps < 2 ? 0 : var*(laps-2.0)/(laps-1.0) + (1.0/laps)*pow(currLap-(totalTime/(laps-1.0)),2);
                totalTime += currLap;
                lastLap = currLap;
                currLap = 0;
            }
            emit updateGUI(id, laps < 1 ? 0 : totalTime / laps, sqrt(var), lastLap, currLap);
        }

    }
}

