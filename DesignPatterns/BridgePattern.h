#include "pch.h"
#include <iostream>
using namespace std;

// decouple an abstraction from implementation, so that two can very independently.

class Image {};
class Snippet {};
class Title {};
class Link {};
class IResource
{
public:
    Image image() { return Image(); };
    Snippet snippet() { return Snippet(); };
    Link link() { return Link(); };
    Title title() { return Title(); };

};
class Artist {};
class ArtistResource : public IResource
{
    Artist artist;
public:

};

class Book {};
class BookResource : public IResource
{
    Book book;
public:

};



class IView
{
protected:
    IResource& resource;
public:
    IView(IResource r):resource(r){}
    virtual void show() = 0;
};

class LongView :public IView
{
public:
    virtual void show()
    {
        resource.image();
    }
};

class ShortView :public IView
{
public:

};











