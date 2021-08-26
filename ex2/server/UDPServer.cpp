#include <string>
#include <sys/socket.h>
#include "UDPServer.h"
#include <unistd.h>
#include <cstring>
#include "Classifier.h"

void UDPServer::send(std::string s) {
    //Send the message to the server
    int sent_bytes = sendto(sock, s.c_str(), strlen(s.c_str()), 0, (struct sockaddr *) &from,
                            sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to sock");
    }
}

std::string UDPServer::recv() {
    //Receive the message from the socket
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[buffer_size];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from sock");
    }
    //Create the string and return it
    std::string msg(buffer);
    return msg;
}

void UDPServer::close() {
    //Close the socket
    ::close(this->sock);
}

UDPServer::UDPServer(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_DGRAM, 0)), from() {
    //Create the socket and check it
    if (sock < 0) {
        perror("error creating sock");
    }
    //Initialize the data structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
    //Bind the socket to the port and ip
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to sock");
    }
}


