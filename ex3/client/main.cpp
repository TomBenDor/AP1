#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "../utils.h"
#include "TCPClient.h"
#include "thread"
#include "queue"
#include "mutex"
#include "condition_variable"

std::condition_variable cv;
std::mutex mutex;

void receiving(std::queue<std::string> &receiving_queue, TCPClient client) {
    while (true) {
        std::string msg = client.recv();
        receiving_queue.push(msg);
        cv.notify_one();
    }
}

std::string receiveFromServer(std::queue<std::string> &receiving_queue) {
    std::unique_lock<std::mutex> uniqueLock(mutex);
    cv.wait(uniqueLock, [&receiving_queue] { return !(receiving_queue.empty()); });
    std::string res = receiving_queue.front();
    receiving_queue.pop();
    return res;
}


int main() {
    //Crete clients
    TCPClient client(inet_addr("127.0.0.1"), htons(55555));
    //Get parameters from user
    std::string parameters;
    std::queue<std::string> msgQueue;
    std::thread receivingThread(receiving, std::ref(msgQueue), client);
    receivingThread.detach();
    //Read the iris data from the csv file
    while (true) {
        std::getline(std::cin, parameters);
        std::vector<std::string> params = utils::split(parameters, ' ');
        if (params[0] == "exit") {
            client.send("exit");
            break;
        }
        std::vector<std::vector<std::string>> unclassified = utils::readCSV(params[0]);
        std::string msg = utils::joinVector(unclassified);
        client.send(msg);
        std::string types = receiveFromServer(msgQueue);
        utils::writeCSV(params[1], utils::split(types, '\n'));
    }
    client.close();
    return 0;
}