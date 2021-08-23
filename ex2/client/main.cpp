#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "vector"
#include "../utils.h"

int main(int argc, char *argv[]) {
    std::vector<std::vector<std::string>> unclassified = readCSV(argv[1]);
    char data[4096];
    strcpy(data, (unclassified[0][0] + " " + unclassified[0][1] + " " + unclassified[0][2] + " " +
                  unclassified[0][3]).c_str());
    const char *ip_address = "127.0.0.1";
    const int port_no = 5555;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating sock");
    }


    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    int data_len = sizeof(data);

    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to sock");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from sock");
    }
    std::cout << "The server sent: " << buffer << std::endl;

    close(sock);

    return 0;
}