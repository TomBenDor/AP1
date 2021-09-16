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

void receiving(std::queue<std::string> &sending_queue, TCPClient client) {
    while (true) {
        std::string msg = client.recv();
        sending_queue.push(msg);
        cv.notify_one();
    }
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
        std::unique_lock<std::mutex> uniqueLock(mutex);
        cv.wait(uniqueLock, [&msgQueue] { return !(msgQueue.empty()); });
        std::string types = msgQueue.front();
        msgQueue.pop();
        utils::writeCSV(params[1], utils::split(types, '\n'));
    }
    client.close();
    cv.notify_one();
    return 0;
}