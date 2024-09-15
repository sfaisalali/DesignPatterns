#ifndef DoubleLinkedList_H
#define DoubleLinkedList_H

#include "IArray.h"
#include "Iterator.h"

template <typename T>
class DoubleLinkedList : public IArray<T>
{
    class Node {
        Node() = delete;
        Node(const Node&) = delete;
        Node& operator = (const Node&) = delete;
        Node* _prev;
        Node* _next;
        T _data;
    public:
        Node(Node* prev, Node* next, T data) : _prev(prev), _next(next), _data(data) {
            if (nullptr != _prev) _prev->SetNext(this);
            if (nullptr != _next) _next->SetPrev(this);
        }
        Node* Prev() { return _prev; }
        Node* Next() { return _next; }
        T Data() { return _data; }
        void SetData(T& data) { _data = data; }
        void SetPrev(Node* prev) { _prev = prev; }
        void SetNext(Node* next) { _next = next; }
    };
    int _size;
    Node* _head;
    Node* _tail;
    Iterator<T>* _iterator;
public:
    DoubleLinkedList() : _size(0), _head(nullptr), _tail(nullptr), _iterator(nullptr) {}

    ~DoubleLinkedList() {}

    virtual int size() { return _size; }

    virtual T getAt(int index) {
        auto item = ItemAt(index);
        if (item == nullptr)
            throw "Invalid Index!.";
        return item->Data();
    }

    virtual void InsertAt(int index, T& var) {
        if (index > _size || index < 0)
            throw "Invalid Index!.";
        else if (index == _size) {
            AddToEnd(var);
            return;
        }
        auto next = ItemAt(index);
        auto prev = next->Prev();

        auto newNode = new Node(prev, next, var);
        if (nullptr == prev)
            _head = newNode;
        else
            prev->SetNext(newNode);
        next->SetPrev(newNode);
        _size++;
    }

    virtual void Add(T obj) {
        AddToEnd(obj);
    }

    virtual void removeAt(int index) {
        if (index < 0 || index >= _size)
            throw "Invalid Index.";
        else if (index == 0) {
            auto temp = _head;
            _head = _head->Next();
            if (nullptr != _head)
                _head->SetPrev(nullptr);
            delete temp;
        }
        else if (index == (_size - 1)) {
            auto temp = _tail;
            _tail = _tail->Prev();
            _tail->SetNext(nullptr);
            delete temp;
        }
        else {
            auto item = ItemAt(index);
            auto prev = item->Prev();
            auto next = item->Next();
            prev->SetNext(next);
            next->SetPrev(prev);
            delete item;
        }
        _size--;
    }

    virtual bool remove(T& obj) {
        auto item = _head;
        while (item != nullptr) {
            if (obj == item->Data()) {
                auto prev = item->Prev();
                auto next = item->Next();
                if (prev == nullptr) { // means, item is the first one.
                    _head = next;
                }
                else {
                    prev->SetNext(next);
                }
                if (next == nullptr) {
                    _tail = prev;
                    prev->SetNext(nullptr);
                }
                else {
                    next->SetPrev(prev);
                }
                delete item;
                --_size;
                return true;
            }
            item = item->Next();
        }
        return false;
    }

    virtual int indexOf(T& obj) {
        auto item = _head;
        int idx = 0;
        while (item != nullptr) {
            if (obj == item->Data()) {
                return idx;
            }
            idx++;
            item = item->Next();
        }
        return -1;
    }
    virtual bool Contains(T& obj) {
        return indexOf(obj) != -1;
    }

    virtual bool isEmpty() {
        return _size == 0;
    }

    virtual void clear() {
        while (_head != nullptr) {
            auto temp = _head;
            _head = _head->Next();
            delete temp;
        }
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    virtual std::string toString() {
        auto item = _head;
        std::string str = "";
        while (item != nullptr) {
            str += item->Data();
            item = item->Next();
        }
        return str;
    }

    virtual IIterator<T>* iterator() {
        delete _iterator;
        _iterator = new Iterator<T>(this);
        return _iterator;
    }

    virtual void SetVal(int idx, T& val) {
        if (idx < 0 || idx >= _size)
            throw "Invalid Index.";
        auto item = ItemAt(idx);
        item->SetData(val);
    }

    virtual void Allocate(int size) {
        if (size <= 0)
            throw "Invalid Size.";
        clear();
        for (int i = 0; i < size; i++) {
            T obj;
            Add(obj);
        }
    }


    virtual void Reverse() {
        _tail = _head;

        auto current = _head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->Next();
            current->SetNext(prev);
            current->SetPrev(next);
            prev = current;
            current = next;
        }
        _head = prev;
    }

    virtual bool HasLoop() {
        auto curr1 = _head;
        auto curr2 = _head;

        int idx = 0;
        while (curr1 != nullptr) {
            idx++;
            if (idx % 2 == 0)
                curr2 = curr2->Next();
            curr1 = curr1->Next();
            if (curr1 == curr2)
                return true;
        }
        return true;
    }

    virtual void RotateLeft(int count) {
        count = count % this->_size;
        if (count == 0)
            return;
        Node* newHead = nullptr;
        Node* itr = _head;
        Node* prev = nullptr;
        for (int i = 0; i < count; i++) {
            prev = itr;
            itr = itr->Next();
        }
        newHead = itr;
        newHead->SetPrev(nullptr);
        prev->SetNext(nullptr);
        while (itr != nullptr && itr->Next()) {
            itr = itr->Next();
        }
        itr->SetNext(_head);
        _head->SetPrev(itr);
        _head = newHead;
        _tail = prev;
    }

    virtual int FindIndex(T obj) {
        return indexOf(obj);
    }

    virtual int NoOfPirsWithSum(T sum)
    {
        auto pivot = FindPivot();
        if (-1 == pivot)return -1;

        auto left = (pivot + 1) % _size; // Modulus is taken to handle scenarios like no rotation and all.
        auto right = pivot;

        auto count = 0;

        while (left != right) {
            auto temp = getAt(left) + getAt(right);
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
    Node* ItemAt(int index) {
        auto temp = _head;
        int idx = 0;
        while (temp != nullptr) {
            if (idx == index) {
                return temp;
            }
            temp = temp->Next();
            idx++;
        }
        return nullptr;
    }

    void AddToEnd(T& data) {
        _tail = new Node(_tail, nullptr, data);
        if (nullptr == _head)
            _head = _tail;
        _size++;
    }

    int FindPivot() {
        auto pivot = _head;
        int idx = 0;
        while (pivot->Next() != nullptr) {
            if (pivot->Data() > pivot->Next()->Data())
                break;
            pivot = pivot->Next();
            idx++;
        }
        return idx;
    }
};

#endif//DoubleLinkedList_H
