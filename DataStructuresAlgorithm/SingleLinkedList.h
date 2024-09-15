#ifndef SingleLinkedList_H
#define SingleLinkedList_H

#include "IArray.h"
#include "Iterator.h"
#include "Stack.h"
#include <stack>

template <typename T>
class SingleLinkedList : public IArray<T>
{
    class Node {
        Node() = delete;
        Node(const Node&) = delete;
        Node& operator = (const Node&) = delete;
        Node* _next;
        T _data;
    public:
        Node(Node* prev, T data) : _next(nullptr), _data(data) {
            if (nullptr != prev) prev->SetNext(this);
        }
        Node* Next() { return _next; }
        T Data() { return _data; }
        void SetData(T& data) { _data = data; }
        void SetNext(Node* next) { _next = next; }
        std::string toString() { return ""; }
    };
    int _size;
    Node* _head;
    Node* _tail;
    Iterator<T>* _iterator;

public:

    SingleLinkedList() : _size(0), _head(nullptr), _tail(nullptr), _iterator(nullptr) {}

    ~SingleLinkedList() {}

    virtual int size() { return _size; }

    virtual T getAt(int index) {
        auto item = ItemAt(index);
        if (item.second == nullptr)
            throw "Invalid Index!.";
        return item.second->Data();
    }

    virtual void InsertAt(int index, T& var) {
        if (index > _size || index < 0)
            throw "Invalid Index!.";
        else if (index == _size) {
            AddToEnd(var);
            return;
        }
        auto item = ItemAt(index);
        auto next = item.second;
        auto newNode = new Node(item.first, var);
        newNode->SetNext(next);
        if (item.first == nullptr)
            _head = newNode;
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
            _head = temp->Next();
            delete temp;
        }
        else {
            auto item = ItemAt(index);
            auto prev = item.first;
            auto next = item.second->Next();
            prev->SetNext(next);
            delete item.second;
        }
        _size--;
    }

    virtual bool remove(T& obj) {
        auto item = _head;
        Node* prev = nullptr;
        while (item != nullptr) {
            if (obj == item->Data()) {
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
                delete item;
                _size--;
                return true;
            }
            prev = item;
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
        item.second->SetData(val);
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

    void Reverse() {
        _tail = _head;

        auto current = _head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->Next();
            current->SetNext(prev);
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
        prev->SetNext(nullptr);
        while (itr != nullptr && itr->Next()) {
            itr = itr->Next();
        }
        itr->SetNext(_head);
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

    std::pair<Node*, Node*> ItemAt(int index) {
        auto temp = _head;
        Node* prev = nullptr;
        int idx = 0;
        while (temp != nullptr) {
            if (idx == index) {
                return std::make_pair(prev, temp);
            }
            prev = temp;
            temp = temp->Next();
            idx++;
        }
        return std::make_pair(nullptr, nullptr);
    }

    void AddToEnd(T& data) {
        _tail = new Node(_tail, data);
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

#endif//SingleLinkedList_H


//
//std::stack<Node*> bb;
//auto head = _head;
//while (head != nullptr) {
//    bb.push(head);
//    head = head->Next();
//}
//Node* newHead = nullptr;
//Node* cur = nullptr;
//Node* prev = nullptr;
//for (int i = 0; i < count; i++) {
//    cur = bb.top();
//    bb.pop();
//    if (newHead == nullptr) {
//        newHead = cur;
//        cur->SetNext(_head);
//    }
//    if (nullptr != prev)
//        prev->SetNext(cur);
//    prev = cur;
//}
//cur = bb.top();
//cur->SetNext(nullptr);
//_head = newHead;
//std::stack<Node*> bb;
//auto head = _head;
//while (head != nullptr) {
//    bb.push(head);
//    head = head->Next();
//}
//Node* newHead = nullptr;
//Node* cur = nullptr;
//Node* prev = nullptr;
//for (int i = 0; i < count; i++) {
//    cur = bb.top();
//    bb.pop();
//    if (newHead == nullptr) {
//        newHead = cur;
//        cur->SetNext(_head);
//    }
//    if (nullptr != prev)
//        prev->SetNext(cur);
//    prev = cur;
//}
//cur = bb.top();
//cur->SetNext(nullptr);
//_head = newHead;