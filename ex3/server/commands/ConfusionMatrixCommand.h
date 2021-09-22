#include "Command.h"
#include "vector"
#include "string"
#include "../Iris.h"

#ifndef TESTING_CONFUSIONMATRIXCOMMAND_H
#define TESTING_CONFUSIONMATRIXCOMMAND_H


class ConfusionMatrixCommand : public Command {
private:
    std::vector<Iris> real, predictions;
public:
    ConfusionMatrixCommand(DefaultIO *, std::vector<Iris>, std::vector<Iris>);

    void execute() override;
};


#endif //TESTING_CONFUSIONMATRIXCOMMAND_H
