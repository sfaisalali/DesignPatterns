#ifndef Queue_H
#define Queue_H

#include "IArray.h"

template <typename T>
class Queue
{
    IArray<T>* _array;
    Queue() = delete;
public:
    Queue(IArray<T>* cont) : _array(cont) {}
    ~Queue() {}
    void Enqueue(T& item) {
        _array->InsertAt(0, item);
    }
    T Dequeue() {
        int pos = _array->size() - 1;
        auto item = _array->getAt(pos);
        _array->removeAt(pos);
        return item;
    }

    T Peek() {
        int pos = _array->size() - 1;
        auto item = _array->getAt(pos);
        return item;
    }

    std::string toString() { return _array->toString(); }

    bool isEmpty() { return size() == 0; }

    int size() { return _array->size(); }

    IIterator<T>* iterator() { return _array->iterator(); }
};

#endif Queue_H