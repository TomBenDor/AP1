#include "utils.h"
#include "iostream"

int main(int argc, char *argv[]) {
    std::vector<std::vector<std::string>> classified = readCSV(argv[1]);
    std::vector<std::vector<std::string>> unclassified = readCSV(argv[2]);
}