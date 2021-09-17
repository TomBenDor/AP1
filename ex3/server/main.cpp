#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "TCPServer.h"
#include "thread"
#include "EuclideanDistance.h"
#include "ChebyshevDistance.h"
#include "ManhattanDistance.h"
#include <unistd.h>

void handleClient(const std::string &path, int clientSock);

int main(int argc, char *argv[]) {
    //Initialize the server according to the command line arguments
    TCPServer server(INADDR_ANY, htons(55555));

    while (true) {
        int clientSock = server.accept();

        std::thread handlingClient(handleClient, argv[1], clientSock);
        handlingClient.detach();
    }
}

void handleClient(const std::string &path, int clientSock) {
    //Get the classified data
    std::vector<Iris> classified = toIrisVector(utils::readCSV(path), true);
    //Initialize the classifier
    ManhattanDistance<Iris> euclideanDistance;
    Distance<Iris> *distance = &euclideanDistance;
    KnnClassifier<Iris> knnClassifier(classified, 5, distance);
    Classifier<Iris> *classifier = &knnClassifier;
    while (true) {
        std::string msg = utils::recv(clientSock);
        if (msg == "exit") {
            break;
        }
        //Get the indices of the irises
        std::vector<std::string> indices = utils::split(msg, '\n');
        std::string types;
        //Classify each of the irises
        for (const std::string &index: indices) {
            Iris iris(utils::split(index, ' '), false);
            types.append(classifier->classify(iris));
            types.append("\n");
        }
        utils::send(clientSock, types);
    }
    close(clientSock);
}