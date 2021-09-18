#include "UploadUnclassified.h"
#include "vector"
#include "../utils.h"


void UploadUnclassified::execute() {
    this->getDefaultIO()->write("Please upload your local train csv file");
    std::string path = this->getDefaultIO()->read();
    std::vector<std::vector<std::string>> file = utils::readCSV(path);
    *this->trainIrises = toIrisVector(file, false);
    this->getDefaultIO()->write("Upload Complete");

    this->getDefaultIO()->write("Please upload your local test csv file");
    path = this->getDefaultIO()->read();
    file = utils::readCSV(path);
    *this->testIrises = toIrisVector(file, false);
    this->getDefaultIO()->write("Upload Complete");
}

UploadUnclassified::UploadUnclassified(DefaultIO *io, std::vector<Iris> *testIrises, std::vector<Iris> *trainIrises) :
        Command("upload an unclassified csv data file", io), testIrises(testIrises), trainIrises(trainIrises) {}
