#include "Command.h"
#include "vector"
#include "Iris.h"

#ifndef CLIENT_UPLOADUNCLASSIFIED_H
#define CLIENT_UPLOADUNCLASSIFIED_H


class UploadUnclassified : public Command {
private:
    std::vector<Iris> *trainIrises;
    std::vector<Iris> *testIrises;
public:
    void execute() override;

    explicit UploadUnclassified(DefaultIO *io, std::vector<Iris> *trainIrises, std::vector<Iris> *testIrises);
};


#endif //CLIENT_UPLOADUNCLASSIFIED_H
