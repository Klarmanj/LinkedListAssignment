#include<iostream>
#include "LinkedListType.h"


using namespace std;

template<class Type>
bool LinkedListType<Type>::isEmpty() const {
    return (first == nullptr);
}
template<class Type>
LinkedListType<Type>::LinkedListType() {
    first = nullptr;
    last = nullptr;
    count = 0;
}
template<class Type>
void LinkedListType<Type>::destroyList() {
    nodeType<Type> *temp;

    while(first != nullptr){
        temp = first;
        first = first->link;
        delete temp;
    }
    last = nullptr;
    count = 0;
}
template<class Type>
void LinkedListType<Type>::initializeList() {
    destroyList();
}
template<class Type>
void LinkedListType<Type>::print() const {

    nodeType<Type> *current;

    current = first;
    while(current != nullptr){
        cout << current->info << " ";
        current = current->link;
    }
}
template<class Type>
int LinkedListType<Type>::length() {
    return count;
}
template<class Type>
Type LinkedListType<Type>::front() const {
    assert(first != nullptr);

    return first->info;
}
template<class Type>
Type LinkedListType<Type>::back() const {
    assert(last != nullptr);

    return last->info;
}
template<class Type>
linkedListIterator<Type> LinkedListType<Type>::begin() {
    linkedListIterator<Type> temp(first);

    return temp;
}
template<class Type>
linkedListIterator<Type> LinkedListType<Type>::end() {
    LinkedListType<Type> temp(nullptr);

    return temp;
}
template<class Type>
void LinkedListType<Type>::copyList(const LinkedListType<Type> & otherList) {
    nodeType<Type> *newNode;
    nodeType<Type> *current;

    if(first != nullptr){
        destroyList();
    }
    if(otherList.first == nullptr){
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else{
        current = otherList.first;

        count = otherList.count;

        first = new nodeType<Type>;

        first->info = current->info;
        first->link = nullptr;

        last = first;

        current = current->link;

        while(current != nullptr){
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->link = nullptr;

            last->link = newNode;
            last = newNode;

            current = current->link;
        }
    }
}
template<class Type>
LinkedListType<Type>::~LinkedListType<Type>() {
    destroyList();
}
template<class Type>
LinkedListType<Type>::LinkedListType(const LinkedListType<Type>& otherList) {
    first = nullptr;
    copyList(otherList);
}
template<class Type>
const LinkedListType<Type>& LinkedListType<Type>::operator=(const LinkedListType<Type> &otherList) {
    if(this != otherList){
        copyList(otherList);
    }
    return *this;
}