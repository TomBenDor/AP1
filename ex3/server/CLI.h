#include "vector"
#include "commands/Command.h"

#ifndef TESTING_CLI_H
#define TESTING_CLI_H

template<class T>
class CLI {
private:
    DefaultIO *io;
    std::vector<Command<T> *> commands;

    void printMenu() {
        std::string msg = "Welcome to the KNN Classifier Server. Please choose an option:";
        for (int i = 0; i < commands.size(); i++) {
            msg.append("\n" + std::to_string(i + 1) + ". " + commands[i]->getDescription());
        }
        msg.append("\n" + std::to_string(commands.size() + 1) + ". exit");
        io->write(msg);
    }

public:
    CLI(DefaultIO *io, std::vector<Command<T> *> commands) : io(io) {
        for (auto i: commands) {
            this->commands.push_back(i);
        }
    }

    void run() {
        while (true) {
            printMenu();
            std::string option = io->read();
            if (option == std::to_string(commands.size() + 1)) {
                io->write("exit");
                break;
            }
            commands[std::stoi(option) - 1]->execute();
        }
    }

    ~CLI() {
        for (auto i: this->commands) {
            delete i;
        }
    }
};


#endif //TESTING_CLI_H
