#include "pch.h"
#include <iostream>
using namespace std;


class IComponent
{
public:
    virtual void FunctionA() = 0;
    virtual void FunctionB() = 0;
};

class ConcreteClass : public IComponent
{
public:
    ConcreteClass() {}
    virtual void FunctionA() { cout << "Concrete class - Function A invoked\n"; }
    virtual void FunctionB() { cout << "Concrete class - Function B invoked\n"; }
};

class DecoratorBase : public IComponent
{
    DecoratorBase() = delete;
protected:
    IComponent& _component;
public:
    DecoratorBase(IComponent& component) : _component(component){}
    virtual void FunctionA() { _component.FunctionA(); cout << "DecoratorBase class - Function A invoked\n"; }
    virtual void FunctionB() { _component.FunctionB(); cout << "DecoratorBase class - Function B invoked\n"; }
};


class Decorator1 : public DecoratorBase
{
    Decorator1() = delete;
public:
    Decorator1(IComponent& component) : DecoratorBase(component) {}
    virtual void FunctionA() { _component.FunctionA(); cout << "Decorator1 class - Function A invoked\n"; }
    virtual void FunctionB() { _component.FunctionB(); cout << "Decorator1 class - Function B invoked\n"; }
};


class Decorator2 : public DecoratorBase
{
    Decorator2() = delete;
public:
    Decorator2(IComponent& component) : DecoratorBase(component) {}
    virtual void FunctionA() { _component.FunctionA(); cout << "Decorator2 class - Function A invoked\n"; }
    virtual void FunctionB() { _component.FunctionB(); cout << "Decorator2 class - Function B invoked\n"; }
};


