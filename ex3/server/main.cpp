#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "TCPServer.h"

int main(int argc, char *argv[]) {
    //Get the classified data
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));
    //Initialize the classifier
    KnnClassifier<Iris> knnClassifier(classified, 5);
    Classifier<Iris> *classifier = &knnClassifier;
    //Initialize the server according to the command line arguments
    TCPServer server(INADDR_ANY, htons(55555));
    int clientSock = server.accept();
    //Receive the message
    std::string msg = server.recv(clientSock);
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
    server.send(clientSock, types);
    //Close the server
    server.close();
    //Free memory
    return 0;
}