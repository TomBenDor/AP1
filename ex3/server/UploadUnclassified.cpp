#include "UploadUnclassified.h"
#include "vector"
#include "Iris.h"
#include "../utils.h"


void UploadUnclassified::execute() {
    this->getDefaultIO()->write("Please upload your local train csv file");
    std::string path = this->getDefaultIO()->read();
    std::vector<std::vector<std::string>> file = utils::readCSV(path);
    std::vector<Iris> trainIrises = toIrisVector(file, false);
    this->getDefaultIO()->write("Upload Complete");

    this->getDefaultIO()->write("Please upload your local test csv file");
    path = this->getDefaultIO()->read();
    file = utils::readCSV(path);
    std::vector<Iris> testIrises = toIrisVector(file, false);
    this->getDefaultIO()->write("Upload Complete");
}

UploadUnclassified::UploadUnclassified(DefaultIO *io) : Command("upload an unclassified csv data file", io) {}
