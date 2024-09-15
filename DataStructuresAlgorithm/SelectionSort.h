#ifndef SelectionSort_H
#define SelectionSort_H
#include "ISort.h"

template <typename T>
class SelectionSort : public ISort<T> {

    SelectionSort() = delete;
public:
    SelectionSort(IArray<T>* arr) : ISort<T>(arr) {

    }
    virtual void AscentingSort() {
        int size = this->_array->size();
        for (int i = 0; i < size - 1; i++) {
            int min = i;
            // finding the min element in the unsorted area.
            for (int j = i; j < size; j++) {
                if (this->_array->getAt(min) > this->_array->getAt(j)) {
                    min = j;
                }
            }
            if (min != i) {
                auto minV = this->_array->getAt(min);
                auto curV = this->_array->getAt(i);
                this->_array->SetVal(min, curV);
                this->_array->SetVal(i, minV);
            }
        }
    }
    virtual void DescentingSort() {
        int size = this->_array->size();
        for (int i = 0; i < size - 1; i++) {
            int min = i;
            // finding the min element in the unsorted area.
            for (int j = i; j < size; j++) {
                if (this->_array->getAt(min) < this->_array->getAt(j)) {
                    min = j;
                }
            }
            if (min != i) {
                auto minV = this->_array->getAt(min);
                auto curV = this->_array->getAt(i);
                this->_array->SetVal(min, curV);
                this->_array->SetVal(i, minV);
            }
        }
    }

};

#endif
