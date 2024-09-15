#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class Pizza
{
    string _sause;
    string _topping;
public:
    void SetSause(string sause) { _sause = sause; }
    void SetTopping(string topping) { _topping = topping; }
    void display() {
        cout << "Pizza with " << _sause << " sause and " << _topping << " topping.\n";
    }
};

class PizzaBuilder {
protected:
    Pizza _pizza;
public:
    const Pizza& pizza() { return _pizza; }
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
};

class TomMashBuilder : public PizzaBuilder {

public:
    virtual void buildSauce() {
        _pizza.SetSause("tomato");
    }
    virtual void buildTopping() {
        _pizza.SetTopping("Mashroom");
    }
};

class SpicyAppleBuilder : public PizzaBuilder {

public:
    virtual void buildSauce() {
        _pizza.SetSause("Chilly");
    }
    virtual void buildTopping() {
        _pizza.SetTopping("Apple");
    }
};

class Cook {
    PizzaBuilder* _builder;
public:
    Cook() : _builder(nullptr) {}
    const Pizza& build(PizzaBuilder* builder) { 
        _builder = builder;
        _builder->buildSauce();
        _builder->buildTopping();
        return _builder->pizza();
    }
};

