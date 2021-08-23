#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "Server.h"
#include "UDPServer.h"


int main(int argc, char *argv[]) {
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));

    KnnClassifier<Iris> knnClassifier(classified, 5);
    Classifier<Iris> *classifier = &knnClassifier;

    UDPServer udpServer(INADDR_ANY, 5555);
    Server *server = &udpServer;

    Iris iris(server->recv());
    server->send(classifier->classify(iris));

    return 0;
}