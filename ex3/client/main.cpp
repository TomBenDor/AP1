#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TCPClient.h"
#include "../utils.h"
#include "thread"

void receiving(TCPClient *client) {
    while (true) {
        const std::string &msg = client->recv();
        if (msg == "exit") {
            client->close();
            exit(0);
        }
        std::cout << msg << std::endl;
    }
}

int main() {
    TCPClient client(inet_addr("127.0.0.1"), htons(55555));

    std::thread thread(receiving, &client);

    while (true) {
        std::string response;
        getline(std::cin, response);
        if (response.rfind("File:", 0) == 0) {
            response = utils::readFile(response.substr(5, response.length()));
        }

        client.send(response);
    }
}