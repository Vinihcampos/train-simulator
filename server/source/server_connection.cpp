#include "header/system_train.h"
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>
#include "header/mainwindow.h"

void server_connection_thread(MainWindow & window) {

    socklen_t client_address_size = sizeof(struct sockaddr);

    // While loop for connections
    while(true) {
        // Waiting for connections
        std::cout << "Waiting for connections." << std::endl;
        System::client_id = accept(System::socket_id, (struct sockaddr *)&System::client_address, &client_address_size);

        if (System::client_id == -1)
            std::cout << "Fail at accepting connection." << std::endl;
        else
            std::cout << "Connection accepted." << std::endl;

        char message[1024];
        int bytesread;
        // While loop for messages
        while (true) {
            bytesread = recv(System::client_id, message, 1024, 0);

            if (bytesread == -1) {
                std::cout << "Message not received." << std::endl;
                continue;
            } else if (bytesread == 0) {
                std::cout << "Connection closed by the client." << std::endl;
                break;
            }
            message[bytesread] = '\0';
            window.interpret_client(message);
			std::cout << message << std::endl;
        }

    }

}
