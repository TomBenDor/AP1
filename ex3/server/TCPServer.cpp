#include "TCPServer.h"
#include <unistd.h>
#include "stdio.h"
#include "cstring"

TCPServer::TCPServer(in_addr_t ip, in_port_t port) : sockId(socket(AF_INET, SOCK_STREAM, 0)), from() {
    //Initialize the socket and check it
    if (sockId < 0) {
        perror("error creating socket");
    }
    //Initialize the data structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
    //Bind the socket to the port and ip
    if (bind(sockId, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(sockId, this->queueLen) < 0) {
        perror("error listening to a socket");
    }
}


int TCPServer::accept() {
    unsigned int addr_len = sizeof(this->from);
    int sock = ::accept(sockId, (struct sockaddr *) &from, &addr_len);
    if (sock < 0) {
        perror("error accepting client");
    }
    return sock;
}

void TCPServer::close() const {
    //Close the socket
    ::close(this->sockId);

}
