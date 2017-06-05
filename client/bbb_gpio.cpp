#include "GPIO-API/include/Pin.h"
#include "GPIO-API/include/GPIOSystem.h"
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <algorithm>

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

using namespace std;

int readAnalog(int number){
       stringstream ss;
       ss << PATH_ADC << number << "_raw";
       fstream fs;
       fs.open(ss.str().c_str(), fstream::in);
       fs >> number;
       fs.close();
       return number;
}

void bbb_potentiometer(char & direction) {
    int potentiomer_value = 0;
    potentiomer_value = readAnalog(1);
    usleep(10000);
    // Set Directions
    if (abs(readAnalog(1) - potentiomer_value) > 10) {
        if (readAnalog(1) - potentiomer_value > 10) direction = 'l';
        else if (readAnalog(1) - potentiomer_value < -10) direction = 'r';
    } else direction = 's';
    if (abs(potentiomer_value - 4096) <= 3) direction = 'l';
    else if (potentiomer_value <= 7) direction = 'r';
}

void bbb_button(std::string pin, bool & button) {
    Pin pin_button {pin, GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};
    button = (pin_button.getValue() == GPIOSystem::Value::HIGH);    
}

