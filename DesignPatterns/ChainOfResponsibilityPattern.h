#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

class IResponsibility {
protected:
    IResponsibility* _next;
public:
    virtual void ExecuteResponsibility(int age) = 0;
    void SetNext(IResponsibility* next) { _next = next; }
};

class School : public IResponsibility {

public:
    void ExecuteResponsibility(int age) {
        if (age < 15)
            cout << "Go to School\n";
        else if (_next != nullptr)
            _next->ExecuteResponsibility(age);
    }
};

class College : public IResponsibility {

public:
    void ExecuteResponsibility(int age) {
        if (age < 22)
            cout << "Go to College\n";
        else if (_next != nullptr)
            _next->ExecuteResponsibility(age);
    }
};

class Job : public IResponsibility {

public:
    void ExecuteResponsibility(int age) {
        if (age < 55)
            cout << "Go for Job\n";
        else if (_next != nullptr)
            _next->ExecuteResponsibility(age);
    }
};

class Retire : public IResponsibility {

public:
    void ExecuteResponsibility(int age) {
        if (age < 70)
            cout << "Retire from Job\n";
        else if (_next != nullptr)
            _next->ExecuteResponsibility(age);
    }
};

class Die : public IResponsibility {

public:
    void ExecuteResponsibility(int age) {
        if (age > 70)
            cout << "You go die\n";
        else if (_next != nullptr)
            _next->ExecuteResponsibility(age);
    }
};
