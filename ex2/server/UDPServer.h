#include "../Socket.h"
#include <netinet/in.h>

#ifndef CLIENT_UDPSERVER_H
#define CLIENT_UDPSERVER_H

class UDPServer : public Socket {
private:
    int sock;
    struct sockaddr_in from;
public:
    UDPServer(in_addr_t ip, in_port_t port);

    void send(std::string string) override;

    std::string recv() override;

    void close() override;

    ~UDPServer() override = default;
};


#endif //CLIENT_UDPSERVER_H
