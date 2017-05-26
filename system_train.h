#ifndef _SYSTEM_
#define _SYSTEM_

#include <vector>
#include <string>
#include "semaforo.h"

class System{
	
	public:
		static std::vector<std::string> logs;
		static std::vector<Semaforo*> semaphores;
		System();
		~System();
        static void clear();
};

#endif
