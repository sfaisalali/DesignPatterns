#include "pch.h"
#include <iostream>
using namespace std;

class IMobileState {
public:
    virtual void Alert() = 0;
};

class Silent : public IMobileState {

public:
    virtual void Alert() {
        cout << "Silent Mode!\n";
    }
};


class OutDoor : public IMobileState {

public:
    virtual void Alert() {
        cout << "OutDoor Mode!\n";
    }
};

class Vibrate : public IMobileState {

public:
    virtual void Alert() {
        cout << "Vibrate Mode!\n";
    }
};

class General : public IMobileState {

public:
    virtual void Alert() {
        cout << "General Mode!\n";
    }
};

class Context {
    IMobileState* _state;
public:
    Context(IMobileState* state = nullptr) : _state(state) {
        if (_state == nullptr) {
            _state = new General();
        }
    }
    void SetState(IMobileState* state) { delete _state;  _state = state; }
    void Alert() {
        _state->Alert();
    }
};
