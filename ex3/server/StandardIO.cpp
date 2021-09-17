#include "StandardIO.h"
#include "iostream"

std::string StandardIO::read() {
    std::string res;
    getline(std::cin, res);
    return res;
}

void StandardIO::write(std::string string) {
    std::cout << string << std::endl;
}
