#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IPage {

    IPage() = delete;
    IPage(const IPage&) = delete;
    IPage& operator = (const IPage&) = delete;
    string _name;
public:
    IPage(string& name) : _name(name){}
    virtual bool isNull() = 0;
    string getName() { return _name; }
};


class KnownePage : public IPage
{
public:
    KnownePage(string str) : IPage(str){}
    virtual bool isNull() { return false; }
};


class UnknownPage : public IPage
{
public:
    UnknownPage(string str) : IPage(str) {}
    virtual bool isNull() { return true; }
};

class Pages {
    vector<string> _pages;
public:
    Pages() {
        _pages.push_back("Home");
        _pages.push_back("Career");
    }
    IPage* GetPage(string pageName) {
        for (auto page : _pages) {
            if (page == pageName)
                return new KnownePage(pageName);
        }
        return new UnknownPage(pageName);
    }
};

