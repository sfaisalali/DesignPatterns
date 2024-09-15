#include "pch.h"
#include <iostream>
using namespace std;

// Here we want the behavior in the adaptee class.
// we are getting that done via the adapter, which contains the adaptee.


class Adaptee
{
public:
    void SpecificRequest() {
        cout << "Invoked Adaptee Function!!!\n";
    }
};

class ITarget
{
public:
    virtual void Request() = 0;
};


// In this file, we are making use of containment rather than inheritance.
// this can be done via multiple inheritance as well.
class AdapterContainment : public ITarget {
    Adaptee& m_adaptee;
    AdapterContainment() = delete;
public:
    AdapterContainment(Adaptee& adaptee) : m_adaptee(adaptee) {}
    virtual void Request() {
        m_adaptee.SpecificRequest();
    }
};

// Multiple inheritance way.
class AdapterMultipleInheritance : public ITarget, public Adaptee {
public:
    virtual void Request() {
        SpecificRequest();
    }
};

