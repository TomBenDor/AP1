#ifndef AP1_COMPARABLE_H
#define AP1_COMPARABLE_H

template<class T>
class Comparable {
private:
    T *type;
public:
    virtual double distance(Comparable<T>) const = 0;

    T getType();
};


#endif //AP1_COMPARABLE_H
