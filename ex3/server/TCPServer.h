#include <netinet/in.h>
#include "string"

#ifndef CLIENT_TCPSERVER_H
#define CLIENT_TCPSERVER_H

class TCPServer {
private:
    int sockId;
    int queueLen = 5;
    struct sockaddr_in from;
    fd_set readfds;
    struct timeval tv;
public:
    TCPServer(in_addr_t ip, in_port_t port);

    int accept();

    void close() const;

    ~TCPServer() = default;
};


#endif //CLIENT_TCPSERVER_H
