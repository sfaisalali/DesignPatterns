#ifndef BubbleSort_H
#define BubbleSort_H
#include "ISort.h"

template <typename T>
class BubbleSort : public ISort<T> {

    BubbleSort() = delete;
public:
    BubbleSort(IArray<T>* arr) : ISort<T>(arr) {

    }
    virtual void AscentingSort() {
        int size = this->_array->size();
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                CompareSwapAscenting(j, j + 1);
            }
        }
    }
    virtual void DescentingSort() {
        int size = this->_array->size();
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                CompareSwapDescenting(j, j + 1);
            }
        }
    }

private:
    void CompareSwapAscenting(int i, int j) {
        CompareSwap(i, j);
    }
    void CompareSwapDescenting(int i, int j) {
        CompareSwap(j, i);
    }
    void CompareSwap(int i, int j) {
        auto first = this->_array->getAt(i);
        auto second = this->_array->getAt(j);

        if (first > second) {
            this->_array->SetVal(i, second);
            this->_array->SetVal(j, first);
        }
    }
};

#endif
