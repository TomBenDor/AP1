#ifndef CLIENT_UDPCLIENT_H
#define CLIENT_UDPCLIENT_H

#include <netinet/in.h>
#include "../Socket.h"

class UDPClient : public Socket {
private:
    int sock;
    struct sockaddr_in sin;
public:
    void send(std::string string) override;

    std::string recv() override;

    void close() override;

    UDPClient(in_addr_t, in_port_t);

    ~UDPClient() override = default;
};


#endif //CLIENT_UDPCLIENT_H
