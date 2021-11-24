#include <iostream>
#include <conio.h>

using namespace std;


template<class Type>
struct nodeType{
    Type info;
    nodeType<Type> *next = nullptr;
    nodeType<Type> *back = nullptr;
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




template<class Type>
linkedListIterator<Type>::linkedListIterator(){
    current = nullptr;
}
template<class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr){
    current = ptr;
}
template<class Type>
Type linkedListIterator<Type>::operator*(){
    return current->info;
}
template<class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++() {
    current = current->next;

    return *this;
}
template<class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type> &right) const {
    return (current == right.current);
}
template<class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type> &right) const {
    return (current != right.current);
}

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
    void reversePrint(nodeType<Type> *current) const;
    void printListReverse() const;
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
        first = first->next;
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
void LinkedListType<Type>::print() const{

    nodeType<Type> *current;

    current = first;
    while(current != nullptr){
        cout << current->info << " ";
        current = current->next;
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
        first->next = nullptr;

        last = first;

        current = current->next;

        while(current != nullptr){
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->next = nullptr;

            last->next = newNode;
            last = newNode;

            current = current->next;
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
    if(this != &otherList){
        copyList(otherList);
    }
    return *this;
}
template<class Type>
void LinkedListType<Type>::reversePrint(nodeType<Type> *current) const{
    if(current != nullptr){
        reversePrint(current->next);
        cout << current->info << " ";

    }
}
template<class Type>
void LinkedListType<Type>::printListReverse() const {
    reversePrint(first);
    cout << endl;
}


template<class Type>
class unorderedLinkedList: public LinkedListType<Type>{
public:
    bool search(const Type&) const;
    void insertFirst(const Type&);
    void insertLast(const Type&);
    void deleteNode(const Type&);
};

template<class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const {
    nodeType<Type> *current;

    current = LinkedListType<Type>::first;
    while(current != nullptr){
        if(current->info == searchItem){
            return true;
        }
        else{
            current = current->link;
        }
        return false;
    }
}

template<class Type>
void unorderedLinkedList<Type>::insertFirst(const Type &newItem) {
    nodeType<Type> *newNode;
    newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = LinkedListType<Type>::first;
    LinkedListType<Type>::first = newNode;
    if(LinkedListType<Type>::last == nullptr){
        LinkedListType<Type>::last = newNode;
    }
}

template<class Type>
void unorderedLinkedList<Type>::insertLast(const Type &newItem) {
    nodeType<Type> *newNode;
    newNode = new nodeType<Type>;

    newNode->info = newItem;
    newNode->link = nullptr;

    if(LinkedListType<Type>::first == nullptr){
        LinkedListType<Type>::first = newNode;
        LinkedListType<Type>::last = newNode;
        LinkedListType<Type>::count++;
    }
}

template<class Type>
void unorderedLinkedList<Type>::deleteNode(const Type &deleteItem) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    bool found;

    if(LinkedListType<Type>::first == nullptr){
        cout << "Cannot delete from an empty list." << endl;
    }
    else{
        if(LinkedListType<Type>::first->info == deleteItem){
            current = LinkedListType<Type>::first;
            LinkedListType<Type>::first = LinkedListType<Type>::first->link;
            LinkedListType<Type>::count--;
            if(LinkedListType<Type>::first == nullptr){
                LinkedListType<Type>::last = nullptr;
            }
            delete current;
        }
        else{
            found = false;
            trailCurrent = LinkedListType<Type>::first;

            current = LinkedListType<Type>::first->link;

            while(current != nullptr && !found){
                if(current->info != deleteItem){
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if(found){
                trailCurrent->link = current->link;
                LinkedListType<Type>::count--;

                if(LinkedListType<Type>::last == current){
                    LinkedListType<Type>::last = trailCurrent;

                    delete current;
                }
                else{
                    cout << "The item to be deleted is not in the list." << endl;
                }
            }
        }
    }
}


template<class Type>
class doublyLinkedList{
public:
    const doublyLinkedList<Type>& operator=(const doublyLinkedList<Type> &);
    void initializeList();
    bool isEmptyList() const;
    void destroy();
    void print() const;
    void reversePrint() const;
    int length() const;
    Type front() const;
    Type back() const;
    bool search(const Type&) const;
    void insertFirst(const Type&);
    void insertLast(const Type&);
    void insertBetween(const Type&);
    void deleteNode(const Type&);
    doublyLinkedList();
    doublyLinkedList(const doublyLinkedList<Type>&);
    ~doublyLinkedList();

protected:
    int count;
    nodeType<Type> *first;
    nodeType<Type> *last;
    nodeType<Type> *ptr;
private:
    void copyList(const doublyLinkedList<Type>&);
};
template<class Type>
void doublyLinkedList<Type>::copyList(const doublyLinkedList<Type> & otherList) {
    nodeType<Type> *newNode;
    nodeType<Type> *current;

    if(first != nullptr){
        destroy();
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
        first->back = current->back;
        first->next = nullptr;

        last = first;

        current = current->next;

        while(current != nullptr){
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->back = current->back;
            newNode->next = nullptr;

            last->next = newNode;
            last->back = newNode;
            last = newNode;

            current = current->next;
        }
    }
}
template<class Type>
const doublyLinkedList<Type> & doublyLinkedList<Type>::operator=(const doublyLinkedList<Type> &otherList) {
    if(this != &otherList){
        copyList(otherList);
    }
    return *this;
}

template<class Type>
doublyLinkedList<Type>::~doublyLinkedList<Type>(){
    destroy();
}

template<class Type>
doublyLinkedList<Type>::doublyLinkedList(const doublyLinkedList<Type> &otherList) {
    copyList(otherList);
}

template<class Type>
void doublyLinkedList<Type>::destroy() {
    nodeType<Type> *temp;

    while(first != nullptr){
        temp = first;
        first = first->next;
        delete temp;
    }
    last = nullptr;
    count = 0;
}

template<class Type>
doublyLinkedList<Type>::doublyLinkedList() {
    first = nullptr;
    last = nullptr;
    count = 0;
}

template<class Type>
bool doublyLinkedList<Type>::isEmptyList() const {
    return (first == nullptr);
}

template<class Type>
void doublyLinkedList<Type>::reversePrint() const {
    nodeType<Type> *current;

    current = last;

    while(current != nullptr){
        cout << current->info << " ";
        current = current->back;
    }
}


template<class Type>
bool doublyLinkedList<Type>::search(const Type &searchItem) const {
    bool found;
    nodeType<Type> *current;

    current = first;

    while(current != nullptr && !found){
        if(current->info >= searchItem){
            found = true;
        }
        else{
            current = current->next;
        }
    }
    if(found){
        found = (current->info == searchItem);
    }
    return  found;


    return findNode(searchItem);
}

template<class Type>
Type doublyLinkedList<Type>::front() const {
    assert(first != nullptr);

    return first->info;
}

template<class Type>
Type doublyLinkedList<Type>::back() const {
    assert(last != nullptr);

    return last->info;
}
template<class Type>
void doublyLinkedList<Type>::insertFirst(const Type &insertItem) {
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;
    newNode->info = insertItem;

    ptr = first;
    if(isEmptyList()){
        first = newNode;
        last= newNode;
        ptr = last;
    }
    else {
        ptr->back = newNode;
        newNode->next = ptr;
        first = newNode;
        ptr = first;
    }
}
template<class Type>
void doublyLinkedList<Type>::insertLast(const Type &insertItem) {
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;
    newNode->info = insertItem;

    ptr = last;
    last = newNode;
    if(isEmptyList()){
        first = newNode;
        ptr = first;
    }
    else{
        ptr->next = newNode;
        newNode->back = ptr;
        ptr = newNode;
    }
    count++;
}

template<class Type>
void doublyLinkedList<Type>::insertBetween(const Type &insertItem) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    nodeType<Type> *newNode;
    bool found;

    newNode = new nodeType<Type>;
    newNode->info = insertItem;
    newNode->next = nullptr;
    newNode->back = nullptr;

    if(first == nullptr){
        first = newNode;
        last = newNode;
        count++;
    }

    else{
        found = false;
        current = first;

        while(current != nullptr && !found){
            if(current->info >= insertItem){
                found = true;
            }
            else{
                trailCurrent = current;
                current = current->next;
            }
            if(current == first){
                first->back = newNode;
                newNode->next = first;
                first = newNode;
                count++;
            }
            else{
                if(current != nullptr){
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    newNode->next = current;
                    current->back = newNode;
                    found = true;
                }
                else{
                    trailCurrent->next = newNode;
                    newNode->back = trailCurrent;
                    last = newNode;
                }
                count++;
            }
        }
    }
}

template<class Type>
void doublyLinkedList<Type>::deleteNode(const Type &deleteItem) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    bool found;

    if(first == nullptr){
        cout << "Cannot delete from an empty list." << endl;
    }
    else if(first->info == deleteItem){
        current = first;
        first = first->next;
        if(first != nullptr){
            first->back = nullptr;
        }
        else{
            last = nullptr;
        }
        count--;

        delete current;
    }
    else{
        found = false;
        current = first;

        while(current != nullptr && !found){
            if(current->info >= deleteItem){
                found = true;
            }
            else{
                current = current->next;
            }
        }
        if(current == nullptr){
            cout << "The item to be deleted is not in the list" << endl;
        }
        else if(current->info == deleteItem){
            trailCurrent = current->back;
            trailCurrent->next = current->next;

            if(current->next != nullptr){
                current->next->back = trailCurrent;
            }
            if(current == last){
                last = trailCurrent;
            }
            count--;
            delete current;
        }
        else{
            cout << "The item to be deleted is not in the list." << endl;
        }
    }
}

template<class Type>
void doublyLinkedList<Type>::initializeList() {
    destroy();
}

template<class Type>
int doublyLinkedList<Type>::length() const {
    return count;
}

template<class Type>
void doublyLinkedList<Type>::print() const {
    nodeType<Type> *current;

    current = first;

    while(current != nullptr){
        cout << current->info;
        current = current->next;
        cout << " ";
    }
}

template<class Type>
class orderedLinkedList: public LinkedListType<Type>{
public:
    bool search(const Type&) const;
    void insert(const Type&);
    void insertFirst(const Type&);
    void insertLast(const Type&);
    void deleteNode(const Type&);

};

template<class Type>
bool orderedLinkedList<Type>::search(const Type &searchItem) const {
    bool found = false;
    nodeType<Type> *current;

    current = this->first;

    while(current != nullptr && !found){
        if(current->info >= searchItem){
            found = true;
        }
        else{
            current = current->next;
        }
    }
    if(found){
        found = (current->info == searchItem);

    }
    return found;
}

template<class Type>
void orderedLinkedList<Type>::insert(const Type &newItem) {
    nodeType<Type>  *current;
    nodeType<Type> *trailCurrent = nullptr;
    nodeType<Type> *newNode;

    bool found;
    newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->next = nullptr;

    if(this->first == nullptr){
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else{
        current = this->first;
        found = false;

        while(current != nullptr && !found){
            if(current->info >= newItem){
                found = true;
            }
            else{
                trailCurrent = current;
                current = current->next;
            }
        }
        if(current == this->first){
            newNode->next = this->first;
            this->first = newNode;
            this->count++;
        }
        else{
            trailCurrent->next = newNode;
            newNode->next = current;

            if(current == nullptr){
                this->last = newNode;
            }
            this->count++;

        }
    }
}

template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type &newItem) {
    insert(newItem);
}

template<class Type>
void orderedLinkedList<Type>::insertLast(const Type &newItem) {
    insert(newItem);
}

template<class Type>
void orderedLinkedList<Type>::deleteNode(const Type &deleteItem) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;

    bool found;

    if(this->first == nullptr){
        cout << "Cannot delete from an empty list." << endl;
    }
    else{
        current = this->first;
        found = false;

        while(current != nullptr && !found){
            if(current->info >= deleteItem){
                found = true;
            }
            else{
                trailCurrent = current;
                current = current->next;
            }
        }
        if(current == nullptr){
            cout << "The item to be deleted is not in the list" << endl;
        }
        else{
            if(current->info == deleteItem){
                if(this->first == current){
                    this->first = this->first->next;

                    if(this->first == nullptr){
                        this->last = nullptr;
                    }
                    delete current;
                }
                else{
                    trailCurrent->next = current->next;

                    if(current == this->last){
                        this->last = trailCurrent;
                    }
                    delete current;
                }
                this->count--;
            }
            else{
                cout << "The item to be deleted is not in the list." << endl;
            }
        }
    }
}


int main(){

    doublyLinkedList<int> list1;
    int num;

    list1.initializeList();
    list1.isEmptyList();
    cout << "Enter numbers and type -999 when you are done." << endl;
    cin >> num;
    while(num != -999){
        list1.insertLast(num);
        cin >> num;
    }
    cout << endl;

    cout << "List 1: " << endl;
    list1.print();
    cout << endl;

    cout << "Enter a number to insert at the beginning of the list: " << endl;
    cin >> num;
    list1.insertFirst(num);

    cout << "List 1 after inserting first: " << endl;
    list1.print();
    cout << endl;

    cout << "Enter a number to insert at the end of the list: " << endl;
    cin >> num;
    list1.insertLast(num);

    cout << "List 1 after inserting last: " << endl;
    list1.print();
    cout << endl;

    cout << "Enter a number to delete from the list: " << endl;
    cin >> num;
    list1.deleteNode(num);

    cout << "List 1 after deleting " << num << endl;
    list1.print();






    return 0;

};