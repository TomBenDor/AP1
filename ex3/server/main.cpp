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

void handleClient(int clientSock);

void printMenu(DefaultIO *io, std::vector<Command<Iris> *> commands);

int main(int argc, char *argv[]) {
    //Initialize the server according to the command line arguments
    TCPServer server(INADDR_ANY, htons(55555));

    while (true) {
        int clientSock = server.accept();

        std::thread handlingClient(handleClient, clientSock);
        handlingClient.detach();
    }
}

void handleClient(int clientSock) {
    KnnClassifier<Iris> knnClassifier;
    ClientData<Iris> data(&knnClassifier);

    SocketIO io(clientSock);
    std::vector<Command<Iris> *> commands = {
            new UploadUnclassifiedCommand<Iris>(&io, &data),
            new ChangeAlgoSettingsCommand<Iris>(&io, &data),
            new ClassifyDataCommand<Iris>(&io, &data),
            new DisplayResultsCommand<Iris>(&io, &data),
            new ConfusionMatrixCommand<Iris>(&io, &data)
    };

    while (true) {
        printMenu(&io, commands);

        std::string option = io.read();
        if (option == std::to_string(commands.size() + 1)) {
            io.write("exit");
            break;
        }
        commands[std::stoi(option) - 1]->execute();
    }

    for (auto command: commands) {
        delete command;
    }
}

void printMenu(DefaultIO *io, std::vector<Command<Iris> *> commands) {
    std::string msg = "Welcome to the KNN Classifier Server. Please choose an option:";
    for (int i = 0; i < commands.size(); i++) {
        msg.append("\n" + std::to_string(i + 1) + ". " + commands[i]->getDescription());
    }
    msg.append("\n" + std::to_string(commands.size() + 1) + ". exit");
    io->write(msg);
}
