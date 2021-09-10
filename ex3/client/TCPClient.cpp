#include <string>
#include <unistd.h>
#include <cstring>
#include "TCPClient.h"

void TCPClient::send(const std::string &string) {
    //Check if the socket is connected to a server
    if (!isConnected) {
        //Connect to the server
        if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            perror("error connecting to server");
        }
        isConnected = true;
    }
    //Send the message
    ssize_t sent_bytes = ::send(sock, string.c_str(), strlen(string.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error writing to sock");
    }
}


std::string TCPClient::recv() const {
    //Read the message from the socket and save in the buffer
    char buffer[4096];
    ssize_t read_bytes = ::recv(sock, buffer, 4096, 0);
    if (read_bytes < 0) {
        perror("error reading from sock");
    }
    //Create a string and return it
    std::string msg(buffer, strlen(buffer));
    return msg;
}

void TCPClient::close() const {
    ::close(this->sock);
}

TCPClient::TCPClient(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_STREAM, 0)), sin() {
    //Initialize the socket and check it
    if (sock < 0) {
        perror("error creating socket");
    }
    //Initialize the data structure
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
}

