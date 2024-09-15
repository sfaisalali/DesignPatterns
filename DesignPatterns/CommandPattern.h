#include "pch.h"
#include <iostream>
#include <list>
using namespace std;

class ICommand
{
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

class Light
{
public:
    void On() { cout << "Light ON.\n"; }
    void Off() { cout << "Light OFF.\n"; }
};

class LightONCommand : public ICommand
{
    Light& m_Light;
    LightONCommand() = delete;
public:
    LightONCommand(Light& light) :m_Light(light) {}
    virtual void Execute() { m_Light.On(); }
    virtual void Undo() { m_Light.Off(); }
};

class LightOFFCommand : public ICommand
{
    Light& m_Light;
    LightOFFCommand() = delete;
public:
    LightOFFCommand(Light& light) :m_Light(light) {}
    virtual void Execute() { m_Light.Off(); }
    virtual void Undo() { m_Light.On(); }
};

class Invoker
{
    std::list<ICommand*> m_Commands;
    ICommand& m_ONcommand;
    ICommand& m_OFFcommand;
    void Execute(ICommand& command) {
        command.Execute();
        m_Commands.push_back(&command);
    }
    Invoker() = delete;
public:
    Invoker(ICommand& ONCommand, ICommand& OFFCommand) : m_ONcommand(ONCommand), m_OFFcommand(OFFCommand){}
    void ON() { Execute(m_ONcommand); }
    void OFF() { Execute(m_OFFcommand); }
    
    void UnDo(){
        if (m_Commands.empty()) {
            cout << "Nothing to do.\n";
            return;
        }
        auto& command = m_Commands.back();
        command->Undo();
        m_Commands.pop_back();
    }
};

