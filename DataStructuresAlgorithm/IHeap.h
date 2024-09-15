#ifndef IHEAP_H
#define IHEAP_H

template<typename T>
class IHeap {

public:
    IHeap() {}
    ~IHeap() {}

    virtual void insert(T obj) = 0;
    virtual void remove(T obj) = 0;
    virtual int parent(int i) = 0;
    virtual int left(int i) = 0;
    virtual int right(int i) = 0;
    virtual T extractMin() = 0;
    virtual T extractMax() = 0;
    virtual T getMin() = 0;
    virtual T getMax() = 0;
    virtual void Heapify(int idx) = 0;

};

#endif//IHEAP_H