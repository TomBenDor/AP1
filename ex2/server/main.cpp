#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "../Socket.h"
#include "UDPServer.h"
#include "TCPServer.h"

int main(int argc, char *argv[]) {
    std::vector<Iris> classified = toIrisVector(readCSV(argv[1]));

    KnnClassifier<Iris> knnClassifier(classified, 5);
    Classifier<Iris> *classifier = &knnClassifier;

    std::string serverType(argv[2]);
    Socket *server = nullptr;
    if (serverType == "TCP") {
        server = new TCPServer(INADDR_ANY, htons(55555));
    } else if (serverType == "UDP") {
        server = new UDPServer(INADDR_ANY, htons(55556));
    } else {
        perror("Unrecognized server type");
    }

    std::string msg = server->recv();
    std::vector<std::string> indices = split(msg, '\n');
    std::string types;
    for (const std::string &index:indices) {
        Iris iris(index);
        types.append(classifier->classify(iris));
        types.append("\n");
    }
    server->send(types);
    server->close();
    delete server;

    return 0;
}