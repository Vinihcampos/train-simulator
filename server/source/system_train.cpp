#include "header/system_train.h"
#include <iostream>

std::vector<std::string> System::logs;
std::vector<Semaforo*> System::semaphores;
struct sockaddr_in System::address;
int System::socket_id;
struct sockaddr_in System::client_address;
int System::client_id;

void System::clear(){
    System::logs.clear();
    for(unsigned int i = 0; i < System::semaphores.size(); ++i){
        delete System::semaphores[i];
    }
    System::semaphores.clear();
}

const std::string System::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &tstruct);

    return buf;
}

System::System(){
}

System::~System(){
    clear();
}
