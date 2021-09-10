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

void TCPServer::send(int clientSock, const std::string &string) {
    //Send the string through the socket
    size_t sent_bytes = ::send(clientSock, string.c_str(), strlen(string.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
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

std::string TCPServer::recv(int clientSock) {
    char buffer[4096];
    int expected_data_len = 4096;
    ssize_t read_bytes = ::recv(clientSock, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        perror("error writing to sock");
    }
    //Create a string and return it
    std::string res(buffer);
    return res;
}
