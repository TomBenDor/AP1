#include <memory>
#include <vector>
#include "Iris.h"
#include "../utils.h"
#include "KnnClassifier.h"
#include "TCPServer.h"
#include "thread"
#include "IO/SocketIO.h"
#include "IO/DefaultIO.h"
#include "ClientData.h"
#include "commands/Command.h"
#include "commands/UploadUnclassifiedCommand.h"
#include "commands/ChangeAlgoSettingsCommand.h"
#include "commands/ConfusionMatrixCommand.h"
#include "commands/ClassifyDataCommand.h"
#include "commands/DisplayResultsCommand.h"
#include "commands/DownloadResultsCommand.h"
#include "CLI.h"

void handleClient(int clientSock);

int main(int argc, char *argv[]) {
    //Initialize the server according to the command line arguments
    TCPServer server(INADDR_ANY, htons(55555));

    while (true) {
        int clientSock = server.accept();

        if (clientSock == -1) {
            break;
        }

        std::thread handlingClient(handleClient, clientSock);
        handlingClient.detach();
    }

    server.close();
}

void handleClient(int clientSock) {
    KnnClassifier<Iris> knnClassifier;
    ClientData<Iris> data(&knnClassifier);
    SocketIO io(clientSock);

    std::vector<std::unique_ptr<Command<Iris>>> commands;
    commands.push_back(std::make_unique<UploadUnclassifiedCommand<Iris>>(&io, &data));
    commands.push_back(std::make_unique<ChangeAlgoSettingsCommand<Iris>>(&io, &data));
    commands.push_back(std::make_unique<ClassifyDataCommand<Iris>>(&io, &data));
    commands.push_back(std::make_unique<DisplayResultsCommand<Iris>>(&io, &data));
    commands.push_back(std::make_unique<DownloadResultsCommand<Iris>>(&io, &data));
    commands.push_back(std::make_unique<ConfusionMatrixCommand<Iris>>(&io, &data));

    CLI<Iris> cli(&io, std::move(commands));
    cli.run();
}
