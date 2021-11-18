#ifndef LINKEDLISTASSIGNMENT_LINKEDLISTITERATOR_H
#define LINKEDLISTASSIGNMENT_LINKEDLISTITERATOR_H

template<class Type>
struct nodeType{
    Type info;
    nodeType<Type> *link;
};

template<class Type>
class linkedListIterator{
public:
    linkedListIterator();
    linkedListIterator(nodeType<Type> *);
    Type operator*();
    linkedListIterator<Type> operator++();
    bool operator==(const linkedListIterator<Type> &) const;
    bool operator!=(const linkedListIterator<Type> &) const;

private:
    nodeType<Type> *current;
};




#endif
