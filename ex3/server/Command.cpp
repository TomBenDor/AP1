#include "Command.h"

#include <utility>

Command::Command(std::string description, DefaultIO *io) : io(io), description(std::move(description)) {

}
