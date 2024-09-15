#include "pch.h"
#include <iostream>

using namespace std;

// Acts as a placeholder for the actual object.


// remote / protection/ virtual proxy
// remote proxy -> when ur data is in a remote location, u have to encapsulate ur request inside the proxy.

// virtual proxy controls access to resources that are expensive to create.
// protection proxy makes sure that onl authorized person is accessing the resource.


// adds additional behavior to control the access the to the object. without changing the interface.

class IBookParser {
public:
    virtual void getnopages() = 0;
};
class Book{};
class BookParser : public IBookParser
{
    Book& _book;
public:
    BookParser(Book& book) : _book(book){ cout << "Actual parsing.\n"; }
    void getnopages()
    {
        cout << "Actual no of pages calculated here.\n";
    }
};

class ProxyBookParser : public IBookParser
{
    Book& _book;
    BookParser* m_pRealSubject;
public:
    ProxyBookParser(Book& book) : m_pRealSubject(nullptr), _book(book) { cout << "Proxy Constructor\n"; }
    void getnopages()
    {
        if (nullptr == m_pRealSubject)
        {
            m_pRealSubject = new BookParser(_book);
        }
        return m_pRealSubject->getnopages();
    }
};
