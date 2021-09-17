#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "../utils.h"
#include "TCPClient.h"
#include "thread"

void handleMessage(const std::string &path, const std::string &msg) {
    utils::writeCSV(path, utils::split(msg, '\n'));
}

void receiving(TCPClient client, std::string &path) {
    while (true) {
        std::string msg = client.recv();
        handleMessage(path, msg);
    }
}


int main() {
    //Crete clients
    TCPClient client(inet_addr("127.0.0.1"), htons(55555));
    //Get parameters from user
    std::string parameters;
    std::string path;
    std::thread receivingThread(receiving, client, std::ref(path));
    receivingThread.detach();
    //Read the iris data from the csv file
    while (true) {
        std::getline(std::cin, parameters);
        std::vector<std::string> params = utils::split(parameters, ' ');
        if (params[0] == "exit") {
            client.send("exit");
            break;
        }
        path = params[1];
        std::vector<std::vector<std::string>> unclassified = utils::readCSV(params[0]);
        std::string msg = utils::joinVector(unclassified);
        client.send(msg);
    }
    client.close();
    return 0;
}