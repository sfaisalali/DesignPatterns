#ifndef DynamicArrayIterator_H
#define DynamicArrayIterator_H

#include "IIterator.h"
#include "IArray.h"


template <typename T>
class Iterator : public IIterator<T>
{
    IArray<T>* _array;
    int _pos;
public:
    Iterator(IArray<T>* arr) : _array(arr), _pos(-1) {}
    ~ Iterator() {}

    virtual bool HasNext()
    {
        return _array->size() > (_pos + 1);
    }
    T Next() {
        _pos++;
        return _array->getAt(_pos);
    }
};

#endif//DynamicArrayIterator_H
