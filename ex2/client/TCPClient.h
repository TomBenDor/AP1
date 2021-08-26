#ifndef CLIENT_TCPCLIENT_H
#define CLIENT_TCPCLIENT_H

#include <netinet/in.h>
#include "../Socket.h"
#include "string"

class TCPClient : public Socket {
private:
    bool isConnected = false;
    int sock;
    struct sockaddr_in sin;
public:
    void send(std::string) override;

    std::string recv() override;

    void close() override;

    TCPClient(in_addr_t, in_port_t);

    ~TCPClient() override = default;
};


#endif //CLIENT_TCPCLIENT_H
