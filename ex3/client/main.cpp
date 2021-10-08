#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include "TCPClient.h"
#include "../utils.h"
#include "thread"

void handleMessage(const std::string &msg);

void receiving(TCPClient *client);

inline bool isFile(const std::string &name);

int main() {
    TCPClient client(inet_addr("127.0.0.1"), htons(55555));

    std::thread thread(receiving, &client);

    while (true) {
        std::string response;
        getline(std::cin, response);
        if (isFile(response)) {
            response = utils::readFile(response);
        }
        client.send(response);
    }
}

void receiving(TCPClient *client) {
    while (true) {
        const std::string &msg = client->recv();
        handleMessage(msg);
    }
}

void handleMessage(const std::string &msg) {
    if (msg == "exit") {
        exit(0);
    }
    std::cout << msg << std::endl;
}

bool isFile(const std::string &name) {
    struct stat buffer{};
    return ((stat(name.c_str(), &buffer) == 0) and (buffer.st_mode & S_IFREG));
}
