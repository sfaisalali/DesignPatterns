#ifndef Stack_H
#define Stack_H

#include "IArray.h"
#include "Iterator.h"

template<typename T>
class Stack {
    IArray<T>* _array;
    Stack() = delete;
public:
    Stack(IArray<T>* cont) : _array(cont) {}
    ~Stack(){}
    void Push(T& item) {
        _array->InsertAt(0, item);
    }
    T Pop() {
        auto item = _array->getAt(0);
        _array->removeAt(0);
        return item;
    }

    T Peek() {
        auto item = _array->getAt(0);
        return item;
    }

    std::string toString() { return _array->toString(); }

    bool isEmpty() { return size() == 0; }

    int size() { return _array->size(); }

    Iterator<T>* iterator() { return _array->iterator(); }
};

#endif//Stack_H
