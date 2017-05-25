#include "trem.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = true;
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

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 20 && y > 30) y-=10;
                else if (y == 30 && x < 120) x+=10;
                else if (x == 120 && y < 330) y+=10;
                else x-=10;
            }
            break;
        case 2:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 120 && y > 30) y-=10;
                else if (y == 30 && x < 320) x+=10;
                else if (x == 320 && y < 130) y+=10;
                else x-=10;
            }
            break;
        case 3:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 320 && y > 30) y-=10;
                else if (y == 30 && x < 520) x+=10;
                else if (x == 520 && y < 130) y+=10;
                else x-=10;
            }
            break;
        case 4:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 520 && y > 30) y-=10;
                else if (y == 30 && x < 620) x+=10;
                else if (x == 620 && y < 330) y+=10;
                else x-=10;
            }
            break;
        case 5:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 320 && y > 230) y-=10;
                else if (y == 230 && x < 520) x+=10;
                else if (x == 520 && y < 330) y+=10;
                else x-=10;
            }
            break;
        case 6:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 120 && y > 230) y-=10;
                else if (y == 230 && x < 320) x+=10;
                else if (x == 320 && y < 330) y+=10;
                else x-=10;
            }
            break;
        case 7:
            if (enable){
                emit updateGUI(id,x,y);
                if (x == 220 && y > 130) y-=10;
                else if (y == 130 && x < 420) x+=10;
                else if (x == 420 && y < 230) y+=10;
                else x-=10;
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

