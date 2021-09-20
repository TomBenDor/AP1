#include "UploadUnclassified.h"
#include "vector"
#include "../utils.h"


void UploadUnclassified::execute() {
    this->getDefaultIO()->write("Please upload your local train csv file");
    std::string input = this->getDefaultIO()->read();
    std::vector<std::string> irises = utils::split(input, '\n');
    std::vector<std::vector<std::string>> trainIrisCoordinates;
    for (const std::string &stringCoordinates: irises) {
        std::vector<std::string> coordinates = utils::split(stringCoordinates, ' ');
        trainIrisCoordinates.push_back(coordinates);
    }
    *this->trainIrises = toIrisVector(trainIrisCoordinates, true);
    this->getDefaultIO()->write("Upload Complete");

    this->getDefaultIO()->write("Please upload your local test csv file");
    input = this->getDefaultIO()->read();
    irises = utils::split(input, '\n');
    std::vector<std::vector<std::string>> testIrisCoordinates;
    for (const std::string &stringCoordinates: irises) {
        std::vector<std::string> coordinates = utils::split(stringCoordinates, ' ');
        testIrisCoordinates.push_back(coordinates);
    }
    *this->testIrises = toIrisVector(testIrisCoordinates, true);
    this->getDefaultIO()->write("Upload Complete");
}

UploadUnclassified::UploadUnclassified(DefaultIO *io, std::vector<Iris> *testIrises, std::vector<Iris> *trainIrises) :
        Command("upload an unclassified csv data file", io), testIrises(testIrises), trainIrises(trainIrises) {}
