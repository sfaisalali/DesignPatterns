#ifndef InsertionSort_H
#define InsertionSort_H
#include "ISort.h"

template <typename T>
class InsertionSort : public ISort<T> {

    InsertionSort() = delete;
public:
    InsertionSort(IArray<T>* arr) : ISort<T>(arr) {

    }
    virtual void AscentingSort() {
        int size = this->_array->size();
        for (int i = 1; i < size; i++) {
            auto temp = this->_array->getAt(i);
            int j = i - 1;
            while ( j >= 0 && this->_array->getAt(j) > temp) {
                auto rr = this->_array->getAt(j);
                this->_array->SetVal(j + 1, rr);
                j--;
            }
            this->_array->SetVal(j + 1, temp);
        }
    }
    virtual void DescentingSort() {
        int size = this->_array->size();
        for (int i = 1; i < size; i++) {
            auto temp = this->_array->getAt(i);
            int j = i - 1;
            while (j >= 0 && this->_array->getAt(j) < temp) {
                auto tt = this->_array->getAt(j);
                this->_array->SetVal(j + 1, tt);
                j--;
            }
            this->_array->SetVal(j + 1, temp);
        }
    }

};

#endif
