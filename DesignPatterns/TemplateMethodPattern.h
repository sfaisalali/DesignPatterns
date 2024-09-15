#include "pch.h"
#include <iostream>
using namespace std;


class IAlgorithm
{
public:
    virtual void Enhance() = 0;
};

class DefaultAlgorithm : public IAlgorithm
{
public:
    virtual void Enhance()
    {
        FuncA();
        FuncB();
        FuncC();
        FuncD();
    }
protected:
    virtual void FuncA() { cout << "default implementation of fucntion A.\n"; }
    virtual void FuncB() { cout << "default implementation of fucntion B.\n"; }
    virtual void FuncC() { cout << "default implementation of fucntion C.\n"; }
    virtual void FuncD() { cout << "default implementation of fucntion D.\n"; }
};


class HookedAlgorithm : public DefaultAlgorithm
{
public:
protected:
    virtual void FuncA() { cout << "Hooked implementation of fucntion A.\n"; }
    virtual void FuncB() { cout << "Hooked implementation of fucntion B.\n"; }
    //virtual void FuncC() { cout << "Hooked implementation of fucntion C.\n"; }
    virtual void FuncD() { cout << "Hooked implementation of fucntion D.\n"; }
};


class IImageEnhancer
{
public:
    virtual void EnhanceImage() = 0;
};

class SomeEnhancer : public IImageEnhancer
{
    IAlgorithm& _algorithm;
    SomeEnhancer() = delete;
public:
    SomeEnhancer(IAlgorithm& algorithm) : _algorithm(algorithm){}
    virtual void EnhanceImage()
    {
        _algorithm.Enhance();
    }
};
