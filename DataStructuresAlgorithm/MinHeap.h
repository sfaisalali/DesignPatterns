#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "Heap.h"

template <typename T>
class MinHeap : public Heap<T> {

public:
    MinHeap(int capacity) : Heap<T>(capacity) {}
    ~MinHeap() {}

    virtual void insert(T obj) {
        // check whether the container is full or not.
        if (this->_capacity <= this->_size) {
            throw "Insufficient space!.";
        }
        auto idx = this->_size;
        this->_size++;
        this->_array[idx] = obj;
        // Now need to check whether the this->parent of current element and this element are in proper order.
        while (this->_size > 0 && this->_array[idx] < this->_array[this->parent(idx)])
        {
            this->Swap(idx, this->parent(idx));
            idx = this->parent(idx);
        }
    }

    virtual void remove(T obj) {}

    virtual void SetLowerValue(int idx, T obj) {
        if (this->_size - 1 <= idx) {
            throw "Invalid Index!.";
        }
        this->_array[idx] = obj;
        while (idx > 0 && this->_array[idx] < this->_array[this->parent(idx)]) {
            this->Swap(idx, this->parent(idx));
            idx = this->parent(idx);
        }
    }

    virtual T extractMin() {
        if (this->_size == 0) {
            return T(INT_MAX);
        }

        else if (this->_size == 1) {
            this->_size = 0;
            return this->_array[0];
        }

        auto ret = this->_array[0];

        // now the size of the heap will be reduced.
        this->_size--;

        // Now, take the largest element in the heap and keep as the first element. then hepify the root.
        this->_array[0] = this->_array[this->_size];

        // then heapify the tree.
        Heapify(0);

        return ret;
    }
    virtual T extractMax() {
        this->_size--;
        return this->_array[this->_size];
    }
    virtual T getMin() { return this->_array[0]; }
    virtual T getMax() { return this->_array[this->_size - 1]; }
    virtual void Heapify(int idx) {
        auto l = this->left(idx);
        auto r = this->right(idx);
        auto small = idx;

        if (l < this->_size && this->_array[l] < this->_array[idx])
            small = l;
        if (r < this->_size && this->_array[r] < this->_array[small])
            small = r;
        if (small != idx) {
            this->Swap(idx, small);
            Heapify(small);
        }
    }
};


#endif//MIN_HEAP_H