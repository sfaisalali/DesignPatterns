#include "pch.h"
#include <iostream>
using namespace std;


class IFlyBehavior
{
public:
    virtual void fly() = 0;
};
class SimpleFlyBehavior : public IFlyBehavior
{
public:
    virtual void fly() { cout << "\nSimple Fly"; }
};
class CrazyFlyBehavior : public IFlyBehavior
{
public:
    virtual void fly() { cout << "\nCrazy Fly"; }
};


class IDisplayBehavior
{
public:
    virtual void Display() = 0;
};
class SimpleDisplayBehavior : public IDisplayBehavior
{
public:
    virtual void Display() { cout << "\nSimple Display"; }
};

class CrazyDisplayBehavior : public IDisplayBehavior
{
public:
    virtual void Display() { cout << "\nCrazy Display"; }
};

class Bird
{
    IDisplayBehavior& _display;
    IFlyBehavior& _fly;
public:
    Bird(IDisplayBehavior& display, IFlyBehavior& fly) : _display(display), _fly(fly) {}
    void fly() { _fly.fly(); }
    void Display() { _display.Display(); }
};

