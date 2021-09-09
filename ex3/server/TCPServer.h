#include "../Socket.h"
#include <netinet/in.h>
#include "string"

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

    ~TCPServer() override = default;
};


#endif //CLIENT_TCPSERVER_H
