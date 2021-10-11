#include <utility>

#include "vector"
#include "commands/Command.h"

#ifndef TESTING_CLI_H
#define TESTING_CLI_H

template<class T>
class CLI {
private:
    DefaultIO *io;
    std::vector<std::unique_ptr<Command<Iris>>> commands;

    void printMenu() {
        std::string msg = "Welcome to the KNN Classifier Server. Please choose an option:";
        for (int i = 0; i < commands.size(); i++) {
            msg.append("\n" + std::to_string(i + 1) + ". " + commands[i]->getDescription());
        }
        msg.append("\n" + std::to_string(commands.size() + 1) + ". exit");
        io->write(msg);
    }

public:
    CLI(DefaultIO *io, std::vector<std::unique_ptr<Command<Iris>>> commands) : io(io), commands(std::move(commands)) {
    }

    void run() {
        while (true) {
            printMenu();
            std::string option = io->read();
            int optionNumber;
            try {
                optionNumber = std::stoi(option) - 1;
            }
            catch (const std::exception &e) {
                io->write("Please enter a number");
                continue;
            }
            if (optionNumber == commands.size()) {
                io->write("exit");
                break;
            }
            if (optionNumber < 0 || optionNumber > commands.size()) {
                io->write("Invalid command");
                continue;
            }
            commands[optionNumber]->execute();
        }
    }
};


#endif //TESTING_CLI_H
