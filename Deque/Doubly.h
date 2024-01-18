#ifndef YOUSSEF
#define YOUSSEF
#include <iostream>
typedef std::string Elem; // instead of making a templated class
class DNode
{
private:
    Elem data;
    DNode *next;
    DNode *prev;
    friend class DLinkedList;
};
class DLinkedList
{
private:
    DNode *header;
    DNode *trailer;

protected:                             // these are called local utilities
    void add(DNode *v, const Elem &e); // insert new node before v
    void remove(DNode *v);             // remove node v
public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const Elem &front() const;
    const Elem &back() const;
    void addFront(const Elem &e);
    void addBack(const Elem &e);
    void removeFront();
    void removeBack();
};
void listReverse(DLinkedList &L)
{
    DLinkedList T;
    while (!L.empty())
    {
        Elem s = L.front();
        L.removeFront();
        T.addFront(s);
    }

    while (!T.empty())
    {
        Elem s = T.front();
        T.removeFront();
        L.addBack(s);
    }
}
DLinkedList::DLinkedList()
{
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    trailer->prev = header;
}
DLinkedList::~DLinkedList()
{
    while (!empty())
        removeFront(); // or removeBack()
    delete header;
    delete trailer;
}
// these are the accessors
bool DLinkedList::empty() const
{
    return (trailer->prev == header);
}
const Elem &DLinkedList::front() const
{
    return (header->next->data);
}
const Elem &DLinkedList::back() const
{
    return (trailer->prev->data);
}
// the implementation of the add utility function in the class, which will enable me to
// make any insert method in the class, whether this insertion is in the front or the back of the list
void DLinkedList::add(DNode *v, const Elem &e)
{
    DNode *u = new DNode;
    u->data = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}
void DLinkedList::addFront(const Elem &e)
{
    add(header->next, e);
}
void DLinkedList::addBack(const Elem &e)
{
    add(trailer, e);
}
void DLinkedList::remove(DNode *v)
{
    v->prev->next = v->next;
    v->next->prev = v->prev;
    delete v;
}
void DLinkedList::removeBack()
{
    remove(trailer->prev);
}
void DLinkedList::removeFront()
{
    remove(header->next);
}
#endif