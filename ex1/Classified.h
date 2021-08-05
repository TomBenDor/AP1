#include "string"
#include "Classifiable.h"

#ifndef AP1_CLASSIFIED_H
#define AP1_CLASSIFIED_H

template<class T>
class Classified : Classifiable<T> {
private:
    std::string type;
public:
    std::string getClass();
};


#endif //AP1_CLASSIFIED_H
