#ifndef HEAP_H
#define HEAP_H

#include "IHeap.h"

template <typename T>
class Heap : IHeap<T> {

private:
    Heap() = delete;

protected:
    T* _array;
    int _capacity;
    int _size;

public:
    Heap(int capacity) : IHeap<T>(), _capacity(capacity), _size(0){
        _array = new T[_capacity];
    }
    ~Heap() {
        delete[] _array;
        _array = nullptr;
    }

    virtual int parent(int i) {
        return (i - 1) / 2;
    }
    virtual int left(int i) {
        return (2 * i) + 1;
    }
    virtual int right(int i) {
        return (2 * i) + 2;
    }

protected:
    void Swap(int x, int y) {
        auto temp = _array[x];
        _array[x] = _array[y];
        _array[y] = temp;
    }
};

#endif//HEAP_H