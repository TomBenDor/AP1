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

    UDPServer udpServer(INADDR_ANY, htons(5555));
    Socket *server = &udpServer;

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

    return 0;
}