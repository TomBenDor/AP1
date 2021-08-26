#include <string>
#include <cstring>
#include <unistd.h>
#include "UDPClient.h"

void UDPClient::send(std::string string) {
    //Send the string through the socket
    int sent_bytes = sendto(sock, string.c_str(), strlen(string.c_str()), 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to sock");
    }
}

std::string UDPClient::recv() {
    //Save the data structure of the server
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[buffer_size];
    //Receive the message
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from sock");
    }
    //Create and return the string
    std::string msg(buffer);
    return msg;
}

void UDPClient::close() {
    //Close the socket
    ::close(sock);
}

UDPClient::UDPClient(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_DGRAM, 0)), sin() {
    //Initialize the socket and check it
    if (sock < 0) {
        perror("error creating sock");
    }
    //Initialize the data structure
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
}
