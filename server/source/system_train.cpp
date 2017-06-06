#include "header/system_train.h"
#include <iostream>
#include <string>
#include <QFileInfo>
#include <fstream>

std::vector<std::string> System::logs;
std::vector<Semaforo*> System::semaphores;
Semaforo * System::logS;
std::string System::log_file;
std::mutex System::mtx;
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
    delete System::logS;
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

void System::updateLog(std::string msg){
    if(System::logs.size() >= 1000){
        if(!System::log_file.compare("")) System::log_file = (QFileInfo(".").absolutePath()).toStdString() + "/server/logs/log_" + System::currentDateTime() + ".txt";
        std::ofstream file(System::log_file, std::ios::out | std::ios::app);
        if (file.is_open()) {
            for(int i = 0; i < System::logs.size(); ++i){
                file << System::logs[i] << std::endl;
            }
            file.close();
            System::logs.clear();
        }else{
            std::cout << "FILE PROBLEM!!!\n";
        }
    }
    
    System::logs.push_back(msg);
}

System::System(){
}

System::~System(){
    clear();
}
