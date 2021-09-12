#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "../utils.h"
#include "TCPClient.h"

int main() {
    //Crete clients
    TCPClient client(inet_addr("127.0.0.1"), htons(55555));
    //Get parameters from user
    std::string parameters;
    std::getline(std::cin, parameters);
    std::vector<std::string> params = utils::split(parameters, ' ');
    //Read the iris data from the csv file
    std::vector<std::vector<std::string>> unclassified = utils::readCSV(params[0]);
    //Set the client according to the request
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
    client.send(msg);
    //Receive the calculated types
    std::string types = client.recv();
    //Write the types to the new file
    utils::writeCSV(params[1], utils::split(types, '\n'));
    //Close the sockets
    client.close();

    return 0;
}