#ifndef ISort_H
#define ISort_H

#include "IArray.h"

template <typename T>
class ISort
{
    ISort() = delete;
protected:
    IArray<T>* _array;
public:
    ISort(IArray<T>* cont) : _array(cont) {}
    virtual ~ISort() { _array = nullptr; }
    virtual void AscentingSort() = 0;
    virtual void DescentingSort() = 0;
    virtual std::string toString() { return _array->toString(); }
};

#endif
