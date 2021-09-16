#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "TCPServer.h"
#include "thread"
#include "EuclideanDistance.h"

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
    EuclideanDistance<Iris> euclideanDistance;
    Distance<Iris> *distance = &euclideanDistance;
    KnnClassifier<Iris> knnClassifier(classified, 5, distance);
    Classifier<Iris> *classifier = &knnClassifier;

    std::string msg = utils::recv(clientSock);
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