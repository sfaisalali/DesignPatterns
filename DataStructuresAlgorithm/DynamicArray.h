#ifndef DynamicArray_H
#define DynamicArray_H

#include <exception>
#include <string>

#include "IArray.h"
#include "Iterator.h"

template <typename T>
class DynamicArray : public IArray<T>
{
private:
    T* _array;
    int _size;
    int _capacity;
    Iterator<T>* _iterator;
public:
    DynamicArray() : DynamicArray(2) {}

    DynamicArray(int capacity) :
        /*IArray<T>(),*/ _capacity(capacity), _size(0), _iterator(nullptr) {
        _array = static_cast<T*>(malloc(sizeof(T) * _capacity));
    }

    ~DynamicArray() {
        free(_array);
        _array = nullptr;
        _size = 0;
        _capacity = 0;
        delete _iterator;
    }

    int size() { return _size; }

    T getAt(int index) {
        if (index < _size)
            return _array[index];
        throw "Invalid Index.";
    }

    void InsertAt(int index, T& var) {
        if (index < _size) {
            // two cases. size = capacity
            if (_size == _capacity) {
                _capacity *= 2;
                auto current = _array;
                _array = static_cast<T*>(malloc(sizeof(T) * _capacity));
                // copy till previous element to the index
                memcpy(_array, current, sizeof(T) * index);

                // Copy remaining after index. keep index position empty. will fill later.
                for (int i = index; i < _size; i++) {
                    _array[i + 1] = current[i];
                }
            }
            else {
                for (int i = _size - 1; i >= index; i--) {
                    _array[i + 1] = _array[i];
                }
            }
            // fill index position.
            _array[index] = var;
            _size++;
        } else {
            throw "Invalid Index.";
        }
    }

    void Add(T obj) {
        if (_size == _capacity) {
            if (_capacity == 0)
                _capacity++;
            else
                _capacity *= 2;
            auto currData = _array;
            _array = static_cast<T*>(malloc(sizeof(T) * _capacity));
            memcpy(_array, currData, sizeof(T) * _size);
            free(currData);
        }
        _array[_size] = obj;
        _size++;
    }

    void removeAt(int index) {
        if (index < _size) {
            for (int idx = index; idx < _size - 1; idx++) {
                _array[idx] = _array[idx + 1];
            }
            _size--;
            return;
        }
        throw "Invalid Index.";
    }

    bool remove(T& obj) {
        auto nIdx = indexOf(obj);
        if (nIdx != -1) {
            removeAt(nIdx);
            return true;
        }
        return false;
    }

    int indexOf(T& obj) {
        for (int nIdx = 0; nIdx < _size; nIdx++) {
            if (_array[nIdx] == obj) {
                return nIdx;
            }
        }
        return -1;
    }

    bool Contains(T& obj) { return indexOf(obj) != -1; }

    bool isEmpty() { return _size == 0; }

    void clear() { _size = 0; }

    std::string toString() {
        std::string str = "";
        for (int idx = 0; idx < _size; idx++) {
            str += _array[idx]/* + ", "*/;
        }
        return str;
    }

    IIterator<T>* iterator() {
        delete _iterator;
        _iterator = new Iterator<T>(this);
        return _iterator;
    }

    virtual void SetVal(int idx, T& val) {
        if (idx < 0 || idx >= _size)
            throw "Invalid Index.";
        _array[idx] = val;
    }

    virtual void Allocate(int size) {
        if (size <= 0)
            throw "Invalid Size.";
        delete _array;
        _array = new T[size];
        _size = size;
        _capacity = size;
    }

    void Reverse() {
        int j = _size - 1;
        for (int i = 0; i <= _size; i++, j--) {
            if (i >= j)return;
            auto temp = _array[i];
            _array[i] = _array[j];
            _array[j] = temp;
        }
    }

    virtual bool HasLoop() { return false; }

    virtual void RotateLeft(int count) {
        count = count % this->_size;
        if (count == 0)
            return;
        auto temp = (T*)malloc(count * sizeof(T));
        memcpy(temp, this->_array, count * sizeof(T));
        
        for (int i = 0; i < _size - count; i++) {
            _array[i] = _array[i + count];
        }
        int j = _size - count;
        for (int i = 0; i < count; i++, j++) {
            _array[j] = temp[i];
        }
    }

    virtual int FindIndex(T obj) {
        return PivotedBinarySearch(obj);
    }

    virtual int NoOfPirsWithSum(T sum)
    {
        auto pivot = FindPivot(0, _size - 1);
        if (-1 == pivot)return -1;

        auto left = (pivot + 1) % _size; // Modulus is taken to handle scenarios like no rotation and all.
        auto right = pivot;

        auto count = 0;

        while (left != right) {
            auto temp = _array[left] + _array[right];
            if (temp == sum) {
                count++;
                // Now need to check whether the indexes cross over. dont want that to happen.
                if (left == (right - 1 + _size) % _size) {
                    return count;
                }
                left = (left + 1) % _size; // Need to handle rotational way. so mod is taken.
                right = (right - 1 + _size) % _size;
            }
            else if (temp < sum) // Sum less than expected?? increment the left.
            {
                left = (left + 1) % _size;
            }
            else // Sum is greater than expected. so decrement the right 
            {
                right = (right - 1 + _size) % _size;
            }
        }
        return count;
    }


private:

    int PivotedBinarySearch(T obj) {
        auto pivot = FindPivot(0, _size - 1);
        // If pivot is -1, that means, we didnt find a pivot.
        // No pivot point menas, the array is not rotated.
        if (pivot == -1)
            return BinarySearch(obj, 0, _size - 1);

        if (_array[pivot] == obj)
            return pivot;

        // Will check with the first element in the array.
        // If the first element in the array is less than or equal to the object to search,
        // then it means that we have to search from first to the pivot element.
        // Because, the current element in the begining was supposed to be next to the right most element if the array was not rotated.
        if (_array[0] <= obj)
            return BinarySearch(obj, 0, pivot - 1);
        //else
        return BinarySearch(obj, pivot + 1, _size - 1);
    }

    int FindPivot(int low, int high) {
        // Not found scenario
        if(high <low)
            return -1;

        // On  reaching the exact mid element.
        if (high == low)
            return low;

        auto mid = (low + high) / 2;
        // Will check the mid element with the next element.
        // if the next element is less than the mid element, then the mid element is the pivot.
        if (mid < high && _array[mid] > _array[mid + 1])
            return mid;
        if (mid > low && _array[mid] < _array[mid - 1])
            return mid - 1;

        // Since we dont find the pivot, we will further divide and find.
        // for that, we will check the values and decide whether to search on the left side or on the right side.

        if (_array[low] < _array[mid])
            return FindPivot(low, mid - 1);
        //else
        return FindPivot(mid + 1, high);
    }

    int BinarySearch(T obj, int low, int high) {

        if (high < low)
            return -1;
        auto mid = (high + low) / 2;
        if (_array[mid] == obj)
            return mid;
        if (obj < _array[mid])
            return BinarySearch(obj, low, mid - 1);
        //else
        return BinarySearch(obj, mid + 1, high);
    }

};

#endif// DynamicArray_H