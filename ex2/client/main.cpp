#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "../utils.h"
#include "../Socket.h"
#include "UDPClient.h"

int main(int argc, char *argv[]) {
    std::vector<std::vector<std::string>> unclassified = readCSV(argv[1]);

    UDPClient udpClient(inet_addr("127.0.0.1"), htons(5555));
    Socket *client = &udpClient;
    std::string msg;
    for (const std::vector<std::string> &i:unclassified) {
        for (const std::string &j:i ) {
            msg.append(j);
            msg.append(" ");
        }
        msg.pop_back();
        msg.append("\n");
    }
    client->send(msg);
    std::cout << client->recv() << std::endl;

    client->close();

    return 0;
}