#include "Command.h"

Command::Command(std::string description, DefaultIO *io) : io(io), description(std::move(description)) {}


DefaultIO *Command::getDefaultIO() {
    return this->io;
}

std::string Command::getDescription() {
    return this->description;
}