#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// assume parent hierarchy.
// Child have two parents. each parent is a child. and they have 2 parents each.. likewise.

// Better example for this is a TODO list!


class ICompositeComponent
{
public:
    virtual void Add() = 0;
};

class CompositeComponent : public ICompositeComponent
{
public:
    virtual void Add()
    {

    }
};

class LeafComponent : public ICompositeComponent
{
public:
protected:
    // Here actualy, the interface is forcing to have an add method. 
    // but htis add method is not needed for this leaf component.
    // No implementeation for add. but blocking user from accessing the same.
    // Made it protected.!!
    virtual void Add() {}
};

///--------------------------------------Below is the example-----------------------------------------///

class IToDo
{
public:
    virtual string GetHtml() = 0;
};

class ToDoItem : public IToDo
{
    string _name;
    ToDoItem() = delete;
public :
    ToDoItem(string ToDoItem) : _name(ToDoItem){}
    virtual string GetHtml()
    {
        return _name;
    }
};


class CollectionOfToDoItems : public IToDo
{
    string _name;
    vector<IToDo*> _ToDoItems;
    CollectionOfToDoItems() = delete;
public:
    CollectionOfToDoItems(string name, vector<IToDo*> ToDoItems) : _name(name), _ToDoItems(ToDoItems) {}
    virtual string GetHtml()
    {
        string html = _name + "\n";
        if(!_ToDoItems.empty())
        {
            html += "<ul>\n";
            for (auto& ToDoItem : _ToDoItems)
            {
                html += ("<li>" + ToDoItem->GetHtml() + "</li>\n");
            }
            html += "</ul>\n";
        }
        return html;
    }
};


