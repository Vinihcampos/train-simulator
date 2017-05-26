#include "trem.h"
#include <iostream>

Trem::Trem(int id, int x, int y, vector<Semaforo*> & semaphores)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 10;
    enable = true;
    this->semaphores = semaphores;
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

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run(){
    while(true){
        switch(id){
            case 1:
                if (enable){
                    emit updateGUI(id,x,y);
                    if (x == 20 && y > 30) {
                        y-=10;
                    }else if (y == 30 && x < 120){
                        if(x == 100) {
                            if(semaphores[0]->getContador()){
                                semaphores[0]->P();
                                x+=10;
                            }
                        }else x+=10;
                    }else if (x == 120 && y < 330){
                        if(y == 150){ 
                            if(!semaphores[0]->getContador()) semaphores[0]->V();
                            y += 10;                                
                        }else if(y == 210){
                            if(semaphores[7]->getContador()){
                                semaphores[7]->P();
                                y+=10;
                            }
                        }
                        else y+=10;
                    }else {
                        if(x == 100) if(!semaphores[7]->getContador()) semaphores[7]->V();
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
                            if(!semaphores[0]->getContador()) semaphores[0]->V();
                            x+=10;
                        }else if(x == 300){
                            if(semaphores[4]->getContador()){
                                semaphores[4]->P();
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        x+=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    x+=10;
                                }
                            }else if(!semaphores[4]->getContador()){
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        x+=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    x+=10;
                                }
                            }
                        }else x+=10;
                    }else if (x == 320 && y < 130){
                        y+=10;
                    }else{
                        if(x == 140) {
                            if(semaphores[0]->getContador()){
                                semaphores[0]->P();
                                x-=10;
                            }
                        }else if(x == 200){
                            if(!semaphores[3]->getContador()) semaphores[3]->V();
                            if(!semaphores[1]->getContador()) semaphores[1]->V();
                            if(!semaphores[4]->getContador()) semaphores[4]->V();
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
                            if(!semaphores[3]->getContador()) semaphores[3]->V();
                            if(!semaphores[1]->getContador()) semaphores[1]->V();
                            if(!semaphores[4]->getContador()) semaphores[4]->V();
                            x+=10;
                        }else if(x == 500){
                            if(semaphores[2]->getContador()){
                                semaphores[2]->P();
                                x+=10;
                            }
                        }
                        else x+=10;
                    }else if (x == 520 && y < 130){
                        y+=10; 
                    }else{
                        if(x == 440){
                            if(semaphores[4]->getContador()){
                                semaphores[4]->P();
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        x-=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    x-=10;
                                }
                            }else if(!semaphores[4]->getContador()){
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        x-=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    x-=10;
                                }
                            }
                        }else if(x == 500) {
                            if(!semaphores[2]->getContador()) {
                                semaphores[2]->V();
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
                            if(semaphores[2]->getContador()){
                                semaphores[2]->P();
                                y-=10;
                            }
                        }else if(y == 210){
                            if(!semaphores[9]->getContador()) semaphores[9]->V();
                            y-=10;
                        }
                        else y-=10;
                    }else if (y == 30 && x < 620){ 
                        if(x == 540) if(!semaphores[2]->getContador()) semaphores[2]->V();
                        x+=10;
                    }else if (x == 620 && y < 330){ 
                        y+=10;
                    }else{
                        if(x == 540){
                            if(semaphores[9]->getContador()){
                                semaphores[9]->P();
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
                            if(!semaphores[6]->getContador()) semaphores[6]->V();
                            if(!semaphores[8]->getContador()) semaphores[8]->V();
                            if(!semaphores[5]->getContador()) semaphores[5]->V();
                            x+=10;
                        }else if(x == 500){
                            if(semaphores[9]->getContador()){
                                semaphores[9]->P();
                                x+=10;
                            }
                        }
                        else x+=10;
                    }else if (x == 520 && y < 330){
                        y+=10;
                    }else{
                        if(x == 340){
                            if(semaphores[5]->getContador()){
                                semaphores[5]->P();
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        x-=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
                                    x-=10;
                                }
                            }else if(!semaphores[5]->getContador()){
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        x-=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
                                    x-=10;
                                }
                            }
                        }else if(x == 500) {
                            if(!semaphores[9]->getContador()) semaphores[9]->V();
                            x-=10;
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
                            if(!semaphores[7]->getContador()) semaphores[7]->V();
                            x+=10;
                        }else if(x == 200){
                            if(semaphores[5]->getContador()){
                                semaphores[5]->P();
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        x+=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
                                    x+=10;
                                }
                            }else if(!semaphores[5]->getContador()){
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        x+=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
                                    x+=10;
                                }
                            }
                        }else x+=10;
                    }else if (x == 320 && y < 330){ 
                        y+=10;
                    }else{
                        if(x == 300){
                            if(!semaphores[6]->getContador()) semaphores[6]->V();
                            if(!semaphores[8]->getContador()) semaphores[8]->V();
                            if(!semaphores[5]->getContador()) semaphores[5]->V();
                            x-=10;
                        }else if(x == 140){
                            if(semaphores[7]->getContador()){
                                semaphores[7]->P();
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
                            if(!semaphores[6]->getContador()) semaphores[6]->V();
                            if(!semaphores[8]->getContador()) semaphores[8]->V();
                            if(!semaphores[5]->getContador()) semaphores[5]->V();
                            y-=10;
                        }else if(y == 150){
                            if(semaphores[4]->getContador()){
                                semaphores[4]->P();
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        y-=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    y-=10;
                                }
                            }else if(!semaphores[4]->getContador()){
                                if(semaphores[1]->getContador()){
                                    semaphores[1]->P();
                                    if(semaphores[3]->getContador()){
                                        semaphores[3]->P();
                                        y-=10;
                                    }
                                }
                                else if(!semaphores[1]->getContador() && semaphores[3]->getContador()){
                                    semaphores[3]->P();
                                    y-=10;
                                }
                            }
                        }else y-=10;
                    }else if (y == 130 && x < 420){
                        x+=10;
                    }else if (x == 420 && y < 230){
                        if(y == 150) {
                            if(!semaphores[3]->getContador()) semaphores[3]->V();
                            if(!semaphores[1]->getContador()) semaphores[1]->V();
                            if(!semaphores[4]->getContador()) semaphores[4]->V();
                            y+=10;
                        }else if(y == 210){
                            if(semaphores[5]->getContador()){
                                semaphores[5]->P();
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        y+=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
                                    y+=10;
                                }
                            }else if(!semaphores[5]->getContador()){
                                if(semaphores[8]->getContador()){
                                    semaphores[8]->P();
                                    if(semaphores[6]->getContador()){
                                        semaphores[6]->P();
                                        y+=10;
                                    }
                                }
                                else if(!semaphores[8]->getContador() && semaphores[6]->getContador()){
                                    semaphores[6]->P();
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
    }
}

