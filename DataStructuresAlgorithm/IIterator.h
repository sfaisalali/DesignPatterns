#ifndef IIterator_H
#define IIterator_H

template <typename T>
class IIterator
{
public:
    IIterator() {}
    virtual ~IIterator() {}
    virtual bool HasNext() = 0;
    virtual T Next() = 0;
};

#endif//IIterator_H
