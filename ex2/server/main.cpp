#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "../Socket.h"
#include "UDPServer.h"
#include "TCPServer.h"

int main(int argc, char *argv[]) {
    //Get the classified data
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));
    //Initialize the classifier
    KnnClassifier<Iris> knnClassifier(classified, 5);
    Classifier<Iris> *classifier = &knnClassifier;
    //Initialize the server according to the command line arguments
    std::string serverType(argv[2]);
    Socket *server;
    if (serverType == "TCP") {
        server = new TCPServer(INADDR_ANY, htons(55555));
    } else if (serverType == "UDP") {
        server = new UDPServer(INADDR_ANY, htons(55556));
    } else {
        perror("Unrecognized server type");
    }
    //Receive the message
    std::string msg = server->recv();
    //Get the indices of the irises
    std::vector<std::string> indices = split(msg, '\n');
    std::string types;
    //Classify each of the irises
    for (const std::string &index: indices) {
        Iris iris(index);
        types.append(classifier->classify(iris));
        types.append("\n");
    }
    //Send the types back
    server->send(types);
    //Close the server
    server->close();
    //Free memory
    delete server;
    return 0;
}