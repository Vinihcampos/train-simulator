#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
 
#define MAXMSG 1024
#define PORTNUM 4325

struct sockaddr_in address;

int connect_client(char * server_ip) {
	// Configuracao de endereco
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;	
	address.sin_port = htons(PORTNUM);
	address.sin_addr.s_addr = inet_addr(server_ip);

	// Criacao de socket
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket_id == -1)
		return -1;
	
	if (connect(socket_id, (struct sockaddr *)&address, sizeof(struct sockaddr)))
		return 0;

	return socket_id;
}


