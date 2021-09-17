#include "Command.h"

#ifndef CLIENT_UPLOADUNCLASSIFIED_H
#define CLIENT_UPLOADUNCLASSIFIED_H


class UploadUnclassified : public Command {
public:
    void execute() override;

    explicit UploadUnclassified(DefaultIO *io);
};


#endif //CLIENT_UPLOADUNCLASSIFIED_H
