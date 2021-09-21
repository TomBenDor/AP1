#include "UploadUnclassified.h"
#include "vector"
#include "../utils.h"


void UploadUnclassified::execute() {
    this->getDefaultIO()->write("Please upload your local train csv file");
    std::string input = this->getDefaultIO()->read();
    *this->trainIrises = stringToIrisVector(input, true);
    this->getDefaultIO()->write("Upload Complete");

    this->getDefaultIO()->write("Please upload your local test csv file");
    input = this->getDefaultIO()->read();
    *this->testIrises = stringToIrisVector(input, true);
    this->getDefaultIO()->write("Upload Complete");
}

UploadUnclassified::UploadUnclassified(DefaultIO *io, std::vector<Iris> *testIrises, std::vector<Iris> *trainIrises) :
        Command("upload an unclassified csv data file", io), testIrises(testIrises), trainIrises(trainIrises) {}
