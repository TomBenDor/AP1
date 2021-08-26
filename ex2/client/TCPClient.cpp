#include <string>
#include <unistd.h>
#include <cstring>
#include "TCPClient.h"

void TCPClient::send(std::string string) {
    if (!isConnected) {
        if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            perror("error connecting to server");
        }
        isConnected = true;
    }
    int sent_bytes = ::send(sock, string.c_str(), strlen(string.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error writing to sock");
    }
}


std::string TCPClient::recv() {
    char buffer[Socket::buffer_size];
    int read_bytes = ::recv(sock, buffer, Socket::buffer_size, 0);
    if (read_bytes < 0) {
        perror("error reading from sock");
    }
    std::string msg(buffer, strlen(buffer));
    return msg;
}

void TCPClient::close() {
    ::close(this->sock);
}

TCPClient::TCPClient(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_STREAM, 0)), sin() {
    if (sock < 0) {
        perror("error creating socket");
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;


}

