#include "TCPServer.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

TCPServer::TCPServer(in_addr_t ip, in_port_t port) : sockId(socket(AF_INET, SOCK_STREAM, 0)), from() {
    if (sockId < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;

    if (bind(sockId, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(sockId, this->queueLen) < 0) {
        perror("error listening to a socket");
    }
}

void TCPServer::send(std::string string) {
    int sent_bytes = ::send(this->clientSock, string.c_str(), strlen(string.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}

std::string TCPServer::recv() {
    if (this->clientSock == 0) {
        unsigned int addr_len = sizeof(this->from);
        this->clientSock = accept(sockId, (struct sockaddr *) &from, &addr_len);

        if (this->clientSock < 0) {
            perror("error accepting client");
        }
    }

    char buffer[Socket::buffer_size];
    int expected_data_len = Socket::buffer_size;
    int read_bytes = ::recv(this->clientSock, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        perror("error writing to sock")
    }
    std::string res(buffer);
    return res;


}

void TCPServer::close() {
    ::close(this->sockId);

}
