#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

class Item
{
private:
    int _idx;
private:
    Item() = delete;
    Item(const Item&) = delete;
    Item& operator = (const Item&) = delete;
public:
    Item(int idx) : _idx(idx) {}
    void Print() {
        cout << "Idx = " << _idx << ".\n";
    }
};

class Iterator {
public:
    virtual bool HasNext() = 0;
    virtual Item* Next() = 0;
    // virtual Item* operator ++ (Item*) = 0;
};

class CollectionIterator : public Iterator {
private:
    vector<Item*>& _vec;
    size_t _currentIdx = -1;
private:
    CollectionIterator() = delete;
    CollectionIterator(const CollectionIterator&) = delete;
    CollectionIterator& operator = (const CollectionIterator&) = delete;
public:
    CollectionIterator(vector<Item*>& vec) : _vec(vec) {}
    virtual bool HasNext()
    {
        return (_currentIdx + 1) < _vec.size();
    }
    virtual Item* Next()
    {
        _currentIdx++;
        return _vec.at(_currentIdx);
    }
};

class ICollection {
public:
    virtual Iterator* GetIterator() = 0;
};

class Collection : public ICollection {
    vector<Item*> _items;
public:
    Collection()
    {
        for(int idx = 0; idx < 10; idx++)
            _items.push_back(new Item(idx));
    }

    Iterator* GetIterator() {
        return new CollectionIterator(_items);
    }
};
