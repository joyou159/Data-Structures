#include <iostream>
#include "Doubly.h"
#include "exception.h"
typedef std::string Elem;
class LinkedDeque
{
public:
    LinkedDeque();
    int size() const;
    bool empty() const;
    const Elem &front() const throw(DequeEmpty);
    const Elem &back() const throw(DequeEmpty);
    void push_front(const Elem &e);
    void push_back(const Elem &e);
    void pop_front() throw(DequeEmpty);
    void pop_back() throw(DequeEmpty);

private:
    DLinkedList D;
    int n; // to maintain the size of the deque.
};
int main()
{

    return 0;
}
LinkedDeque::LinkedDeque() : D(), n(0) {}
int LinkedDeque::size() const { return n; }
bool LinkedDeque::empty() const { return (n == 0); }
const Elem &LinkedDeque::front() const throw(DequeEmpty)
{
    if (n == 0)
        throw DequeEmpty("the Deque is empty!");
    return D.front();
}
const Elem &LinkedDeque::back() const throw(DequeEmpty)
{
    if (n == 0)
        throw DequeEmpty("the Deque is empty");
    return D.back();
}
void LinkedDeque::push_front(const Elem &e)
{
    D.addFront(e);
    n++;
}
void LinkedDeque::push_back(const Elem &e)
{
    D.addBack(e);
    n++;
}
void LinkedDeque::pop_front() throw(DequeEmpty)
{
    if (n == 0)
        throw DequeEmpty("the Deque is empty!");
    D.removeFront();
    n--;
}
void LinkedDeque::pop_back() throw(DequeEmpty)
{
    if (n == 0)
        throw DequeEmpty("the Deque is empty!");
    D.removeBack();
    n--;
}
