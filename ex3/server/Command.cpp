#include "Command.h"

#include <utility>

Command::Command(const std::string &description, DefaultIO *io) : io(io), description(std::move(description)) {

}
