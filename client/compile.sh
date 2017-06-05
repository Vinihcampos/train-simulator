g++ -c panels.cpp "GPIO-API/src/Pin.cpp" "GPIO-API/src/GPIOSystem.cpp" -lncurses -lmenu -lpanel -pthread -std=c++11 -I "GPIO-API/include"
g++ panels.o Pin.o GPIOSystem.o -o panels -lncurses -lmenu -lpanel -pthread -std=c++11 
