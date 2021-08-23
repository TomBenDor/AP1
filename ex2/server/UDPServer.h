#include "Server.h"
#include <netinet/in.h>

#ifndef CLIENT_UDPSERVER_H
#define CLIENT_UDPSERVER_H

class UDPServer : public Server {
private:
    int sock;
    struct sockaddr_in from;
public:
    UDPServer(int ip, int port);

    void send(std::string string) override;

    std::string recv() override;

    void close() override;
};


#endif //CLIENT_UDPSERVER_H
