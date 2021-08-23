#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "../Socket.h"
#include "UDPServer.h"


int main(int argc, char *argv[]) {
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));

    KnnClassifier<Iris> knnClassifier(classified, 5);
    Classifier<Iris> *classifier = &knnClassifier;

    UDPServer udpServer(INADDR_ANY, htons(5555));
    Socket *server = &udpServer;

    Iris iris(server->recv());
    server->send(classifier->classify(iris));
    server->close();

    return 0;
}