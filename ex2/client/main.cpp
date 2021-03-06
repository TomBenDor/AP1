#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "../utils.h"
#include "../Socket.h"
#include "UDPClient.h"
#include "TCPClient.h"

int main(int argc, char *argv[]) {
    //Crete clients
    UDPClient udpClient(inet_addr("127.0.0.1"), htons(55556));
    TCPClient tcpClient(inet_addr("127.0.0.1"), htons(55555));
    //Get parameters from user
    std::string parameters;
    std::getline(std::cin, parameters);
    std::vector<std::string> params = split(parameters, ' ');
    //Read the iris data from the csv file
    std::vector<std::vector<std::string>> unclassified = readCSV(params[1]);
    //Set the client according to the request
    Socket *client;
    if (params[0] == "TCP") {
        client = &tcpClient;
    } else if (params[0] == "UDP") {
        client = &udpClient;
    } else {
        perror("Unrecognized client type");
    }
    //Split the data in order to send it
    std::string msg;
    for (const std::vector<std::string> &i: unclassified) {
        for (const std::string &j: i) {
            msg.append(j);
            msg.append(" ");
        }
        msg.pop_back();
        msg.append("\n");
    }
    msg.pop_back();
    //Send the message
    client->send(msg);
    //Receive the calculated types
    std::string types = client->recv();
    //Write the types to the new file
    writeCSV(params[2], split(types, '\n'));
    //Close the sockets
    udpClient.close();
    tcpClient.close();

    return 0;
}