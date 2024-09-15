#ifndef QuickSort_H
#define QuickSort_H
#include "ISort.h"

template <typename T>
class QuickSort : public ISort<T> {

    QuickSort() = delete;
public:
    QuickSort(IArray<T>* arr) : ISort<T>(arr) {

    }
    virtual void AscentingSort() {
        int size = this->_array->size();
        QuickSortAsc(0, size - 1);
    }
    virtual void DescentingSort() {
        throw std::exception("\n" __FUNCTION__ " - Not Implemented!");
    }

private:

    void QuickSortAsc(int start, int end) {
        if (start < end) {
            auto loc = PivotAsc(start, end);
            QuickSortAsc(start, loc - 1);
            QuickSortAsc(loc + 1, end);
        }
    }
    int PivotAsc(int lb, int ub) {
        int start = lb;
        int end = ub;
        auto pivot = this->_array->getAt(start);
        while (start < end) {
            while (this->_array->getAt(start) <= pivot) {
                start++;
            }
            while (this->_array->getAt(end) > pivot) {
                end--;
            }
            // swaping is done only if start < end
            if (start < end) {
                Swap(start, end);
            }
        }
        Swap(lb, end);
        return end;
    }

    void Swap(int i, int j) {
        auto ii = this->_array->getAt(i);
        auto jj = this->_array->getAt(j);
        this->_array->SetVal(i, jj);
        this->_array->SetVal(j, ii);
    }

};

#endif
