#include <utility>
#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "Classifier.h"
#include "TCPServer.h"
#include "pthread.h"
#include "EuclideanDistance.h"
#include "ChebyshevDistance.h"
#include "ManhattanDistance.h"

void *handleClient(void *);

class Config {
public:
    std::string path;
    int clientSock;

    Config(std::string path, int clientSock) : path(std::move(path)), clientSock(clientSock) {}
};

int main(int argc, char *argv[]) {
    //Initialize the server according to the command line arguments
    TCPServer server(INADDR_ANY, htons(55555));

    std::vector<Config> configurations;

    while (true) {
        int clientSock = server.accept();

        pthread_t tid;
        std::string path = argv[1];
        Config config(path, clientSock);
        configurations.push_back(config);
        pthread_create(&tid, nullptr, handleClient, &configurations[configurations.size() - 1]);
    }
}

void *handleClient(void *c) {
    auto *config = (Config *) c;
    //Get the classified data
    std::vector<Iris> classified = toIrisVector(utils::readCSV(config->path), true);
    //Initialize the classifier
    ManhattanDistance<Iris> euclideanDistance;
    Distance<Iris> *distance = &euclideanDistance;
    KnnClassifier<Iris> knnClassifier(classified, 5, distance);
    Classifier<Iris> *classifier = &knnClassifier;

    std::string msg = utils::recv(config->clientSock);
    //Get the indices of the irises
    std::vector<std::string> indices = utils::split(msg, '\n');
    std::string types;
    //Classify each of the irises
    for (const std::string &index: indices) {
        Iris iris(utils::split(index, ' '), false);
        types.append(classifier->classify(iris));
        types.append("\n");
    }
    utils::send(config->clientSock, types);
    return nullptr;
}