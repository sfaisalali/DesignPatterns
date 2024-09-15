#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "Heap.h"

template <typename T>
class MaxHeap : public Heap<T> {

public:
    MaxHeap(int capacity) : Heap<T>(capacity){}
    ~MaxHeap() {}
    virtual void insert(T obj) {
        // check whether the container is full or not.
        if (this->_capacity <= this->_size) {
            throw "Insufficient space!.";
        }
        auto idx = this->_size;
        this->_size++;
        this->_array[idx] = obj;
        // Now need to check whether the parent of current element and this element are in proper order.
        while (this->_size > 0 && this->_array[idx] > this->_array[this->parent(idx)])
        {
            this->Swap(idx, this->parent(idx));
            idx = this->parent(idx);
        }
    }
    virtual void remove(T obj) {}
    virtual T extractMin() {
        this->_size--;
        return this->_array[this->_size];
    }
    virtual T extractMax() {
        if (this->_size == 0) {
            return T(INT_MIN);
        }

        else if (this->_size == 1) {
            this->_size = 0;
            return this->_array[0];
        }

        auto ret = this->getMax();

        // Now, take the smallest element in the heap and keep as the first element. then hepify the root.
        this->_array[0] = getMin();

        // now the size of the heap will be reduced.
        this->_size--;

        // then heapify the tree.
        Heapify(0);

        return ret;
    }
    virtual T getMin() { return this->_array[this->_size - 1]; }
    virtual T getMax() { return this->_array[0]; }
    virtual void Heapify(int idx) {
        auto l = this->left(idx);
        auto r = this->right(idx);
        auto large = idx;

        if (l < this->_size && this->_array[l] > this->_array[idx])
            large = l;
        if (r < this->_size && this->_array[r] > this->_array[large])
            large = r;
        if (large != idx) {
            this->Swap(idx, large);
            Heapify(large);
        }
    }
};


#endif//MIN_HEAP_H