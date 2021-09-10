#ifndef CLIENT_TCPCLIENT_H
#define CLIENT_TCPCLIENT_H

#include <netinet/in.h>
#include "string"

class TCPClient {
private:
    bool isConnected = false;
    int sock;
    struct sockaddr_in sin;
public:
    void send(const std::string &);

    std::string recv() const;

    void close() const;

    TCPClient(in_addr_t, in_port_t);

    ~TCPClient() = default;
};


#endif //CLIENT_TCPCLIENT_H
