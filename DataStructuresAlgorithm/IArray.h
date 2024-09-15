#ifndef _IARRAY_H
#define _IARRAY_H
#include <string>
#include "IIterator.h"

template <typename T>
class IArray
{
public :
    IArray() {}

    virtual ~IArray() { }

    virtual int size() = 0;

    virtual T getAt(int index) = 0;

    virtual void InsertAt(int index, T& var) = 0;

    virtual void Add(T obj) = 0;

    virtual void removeAt(int index) = 0;

    virtual bool remove(T& obj) = 0;

    virtual int indexOf(T& obj) = 0;

    virtual bool Contains(T& obj) = 0;

    virtual bool isEmpty() = 0;

    virtual void clear() = 0;

    virtual std::string toString() = 0;

    virtual IIterator<T>* iterator() = 0;

    virtual void SetVal(int idx, T& val) = 0;

    virtual void Allocate(int size) = 0;

    virtual void Reverse() = 0;

    virtual bool HasLoop() = 0;

    virtual void RotateLeft(int times) = 0;

    virtual int FindIndex(T obj) = 0;

    virtual int NoOfPirsWithSum(T sum) = 0;

    operator std::string() { return toString(); }

};
#endif// _IARRAY_H