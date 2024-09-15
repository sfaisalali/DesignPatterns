#ifndef MergeSort_H
#define MergeSort_H
#include "ISort.h"

template <typename T>
bool AscCompareFunc(T i, T j) {
    return i < j;
}

template <typename T>
bool DescCompareFunc(T i, T j) {
    return i > j;
}

template <typename T>
class MergeSort : public ISort<T> {

    IArray<T>* _newArray;

    MergeSort() = delete;

public:

    MergeSort(IArray<T>* arr) : ISort<T>(arr) {
        _newArray = new DoubleLinkedList<T>;
        _newArray->Allocate(arr->size());
    }

    virtual void AscentingSort() {
        Sort(0, this->_array->size() - 1, &AscCompareFunc);
    }

    virtual void DescentingSort() {
        Sort(0, this->_array->size() - 1, &DescCompareFunc);
    }

private:


    void Sort(int low, int high, bool(*funcName)(T, T)) {
        if (low >= high)return;
        auto mid = low + high;
        mid /= 2;
        Sort(low, mid, funcName);
        Sort(mid + 1, high, funcName);
        Merge(low, mid, high, funcName);
    }

    void Merge(int low, int mid, int high, bool(*funcName)(T, T)) {
        int i = low;
        int j = mid + 1;
        int k = low;
        while (i <= mid && j <= high) {
            if ((*funcName)(this->_array->getAt(i), this->_array->getAt(j))) {
                auto obj = this->_array->getAt(i);
                _newArray->SetVal(k, obj);
                i++;
            }
            else {
                auto obj = this->_array->getAt(j);
                _newArray->SetVal(k, obj);
                j++;
            }
            k++;
        }
        while (i <= mid) {
            auto obj = this->_array->getAt(i);
            _newArray->SetVal(k, obj);
            i++;
            k++;
        }
        while (j <= high) {
            auto obj = this->_array->getAt(j);
            _newArray->SetVal(k, obj);
            j++;
            k++;
        }
        CopyBuffer(low, k);
    }
    
    void CopyBuffer(int low, int high) {
        for (int i = low; i < high; i++) {
            auto obj = _newArray->getAt(i);
            this->_array->SetVal(i, obj);
        }
    }
};

#endif