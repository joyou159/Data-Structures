#ifndef YOUSSEF
#define YOUSSEF
#include <iostream>
typedef std::string Elem;
class CNode
{
    Elem data;
    CNode *next;
    friend class CLinkedList;
};
class CLinkedList
{
public:
    CLinkedList();
    ~CLinkedList();
    bool empty() const;
    const Elem &front() const; // get the data member of the node which follows the cursor referenced node.
    const Elem &back() const;  // get the data member of the node referenced by the cursor.
    void advance();
    void add(const Elem &e); // insert new node just after the cursor.
    void remove();           // remove the front node.

private:
    CNode *cursor;
};

CLinkedList::CLinkedList()
{
    cursor = nullptr;
}
CLinkedList::~CLinkedList()
{
    while (!empty())
    {
        remove(); // we consider that remove() method delete the node.
    }
}
bool CLinkedList::empty() const
{
    return (cursor == NULL);
}
const Elem &CLinkedList::front() const
{
    return (cursor->next->data);
}
const Elem &CLinkedList::back() const
{
    return (cursor->data);
}
void CLinkedList::advance()
{
    cursor = cursor->next;
}
void CLinkedList::add(const Elem &e)
{
    if (cursor == NULL)
    {
        cursor = new CNode;
        cursor->data = e;
        cursor->next = cursor;
    }
    else
    {
        CNode *v = new CNode;
        v->data = e;
        v->next = cursor->next;
        cursor->next = v;
    }
}
void CLinkedList::remove()
{
    if (cursor->next == cursor)
    {
        delete cursor;
        cursor = NULL;
    }
    else
    {
        CNode *old = cursor->next;
        cursor->next = old->next;
        delete old;
    }
}
#endif