#include "header/mainwindow.h"
#include <QApplication>
#include "header/system_train.h"
#include <iostream>
#include "server_connection.cpp"

#define PORTNUM 4325
#define SERVER_IP "192.168.7.1"

int main(int argc, char *argv[])
{
    // Configuring address
    memset(&System::address, 0, sizeof(System::address));
    System::address.sin_family = AF_INET;
    System::address.sin_port = htons(PORTNUM);
    System::address.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Creating socket
    System::socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (System::socket_id == -1)
        std::cout << "Error when creating socket." << std::endl;
    else
        std::cout << "Socket created for port " << PORTNUM << std::endl;

    // Binding socket to a port
    if (bind(System::socket_id, (struct sockaddr *)&System::address, sizeof(struct sockaddr)) == -1)
        std::cout << "Fail to bind to a port." << std::endl;
    else
        std::cout << "Socket binded to a port." << std::endl;

    // Enabling server to listen to connections
    if (listen(System::socket_id, 10) == -1)
        std::cout << "Fail to enable listening." << std::endl;
    else
        std::cout << "The server is now listening for connections." << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::thread thread_connection(server_connection_thread, ref(w));
    thread_connection.detach();


    return a.exec();
}
