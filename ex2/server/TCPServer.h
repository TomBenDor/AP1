#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "../Socket.h"

#ifndef CLIENT_TCPSERVER_H
#define CLIENT_TCPSERVER_H

class TCPServer : public Socket {
private:
    int sockId;
    int queueLen = 5;
    struct sockaddr_in from;
    int clientSock = 0;
public:
    TCPServer(in_addr_t ip, in_port_t port);

    void send(std::string string) override;

    std::string recv() override;

    void close() override;

};


#endif //CLIENT_TCPSERVER_H
