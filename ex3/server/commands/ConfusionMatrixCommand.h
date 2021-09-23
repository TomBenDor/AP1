#include "Command.h"
#include "vector"
#include "string"
#include "../Iris.h"
#include "../KnnClassifier.h"

#ifndef TESTING_CONFUSIONMATRIXCOMMAND_H
#define TESTING_CONFUSIONMATRIXCOMMAND_H


class ConfusionMatrixCommand : public Command {
private:
    std::vector<Iris> real, predictions;
    KnnClassifier<Iris> *classifier;
public:
    ConfusionMatrixCommand(DefaultIO *, std::vector<Iris>, std::vector<Iris>, KnnClassifier<Iris> *);

    void execute() override;
};


#endif //TESTING_CONFUSIONMATRIXCOMMAND_H
