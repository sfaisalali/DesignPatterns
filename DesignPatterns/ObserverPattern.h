#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;


class IObserver
{
public:
    virtual void Update() = 0;
};

class TabView : public IObserver
{
public:
    virtual void Update()
    {
        cout << "\n Updated in tab view";
    }
};

class TreeView : public IObserver
{
public:
    virtual void Update()
    {
        cout << "\n Updated in tree view";
    }
};

class IObservable
{
public:
    virtual void Add(IObserver* observer) = 0;
    virtual void Remove(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

class WhetherStation : public IObservable
{
    vector<IObserver*> _observers;
public:
    virtual void Add(IObserver* observer) {        _observers.push_back(observer);    }
    virtual void Remove(IObserver* observer)
    {
        for (auto item = _observers.begin(); item < _observers.end(); item++) {
            if (*item != observer) continue;
            _observers.erase(item);
            break;
        }
    }
    virtual void Notify()
    {
        for (auto item : _observers)
        {
            item->Update();
        }
    }
};

