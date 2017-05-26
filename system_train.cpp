#include "system_train.h"
#include <iostream>

std::vector<std::string> System::logs;
std::vector<Semaforo*> System::semaphores;

void System::clear(){
    System::logs.clear();
    for(unsigned int i = 0; i < System::semaphores.size(); ++i){
        delete System::semaphores[i];
    }
    System::semaphores.clear();
}

System::System(){
}

System::~System(){
    clear();
}
