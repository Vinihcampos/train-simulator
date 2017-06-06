#ifndef _SYSTEM_
#define _SYSTEM_

#include <vector>
#include <string>
#include "semaforo.h"
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close

class System{
	
	public:
        static struct sockaddr_in address;
        static struct sockaddr_in client_address;
        static int socket_id;
        static int client_id;
		static std::vector<std::string> logs;
		static std::vector<Semaforo*> semaphores;
		System();
		~System();
        static void clear();
        static const std::string currentDateTime();
};

#endif
