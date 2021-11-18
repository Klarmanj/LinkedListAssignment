#ifndef LINKEDLISTASSIGNMENT_LINKEDLISTTYPE_H
#define LINKEDLISTASSIGNMENT_LINKEDLISTTYPE_H
#include "LinkedListIterator.h"

template<class Type>
class LinkedListType {
public:
    const LinkedListType<Type>& operator=(const LinkedListType<Type>&);
    void initializeList();
    bool isEmpty() const;
    void print() const;
    int length();
    void destroyList();
    Type front() const;
    Type back() const;
    virtual bool search(const Type&) const = 0;
    virtual void insertFirst(const Type&) = 0;
    virtual void insertLast(const Type&) = 0;
    virtual void deleteNode(const Type&) = 0;
    linkedListIterator<Type> begin();
    linkedListIterator<Type> end();
    LinkedListType();
    LinkedListType(const LinkedListType<Type>&);
    ~LinkedListType();

protected:
    int count;
    nodeType<Type> *first;
    nodeType<Type> *last;
private:
    void copyList(const LinkedListType<Type>&);
};


#endif
