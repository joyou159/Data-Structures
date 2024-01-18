#include <iostream>
#include "exception.h"
#include "CircleList.cpp"
typedef std::string Elem;
class LinkedQueue
{
public:
    LinkedQueue(); // we do not need a destructor as the circleList already has one
    int size() const;
    bool empty() const;
    const Elem &front() const throw(QueueEmpty);
    void dequeue() throw(QueueEmpty);
    void enqueue(const Elem &e);

private:
    CLinkedList c;
    int n; // as the CLinkedList does not provide a size function, we will count the number of elements which are enqueued.
};
int main()
{
    LinkedQueue names;
    names.enqueue("youssef");
    names.enqueue("Ahmed");
    std::cout << names.front();
    names.dequeue();
    std::cout << names.front();
}
LinkedQueue::LinkedQueue() : c(), n(0) {}
int LinkedQueue::size() const
{
    return n;
}
bool LinkedQueue::empty() const
{
    return (n == 0);
}
const Elem &LinkedQueue::front() const throw(QueueEmpty)
{
    if (n == 0)
    {
        throw QueueEmpty("the Queue is empty!");
    }
    return c.front();
}
void LinkedQueue::dequeue() throw(QueueEmpty)
{
    if (n == 0)
        throw QueueEmpty("the Queue is empty!");

    c.remove();
    n--;
}
void LinkedQueue::enqueue(const Elem &e)
{
    c.add(e);
    c.advance(); // to advance the cursor which is in this case the rear of the Queue.
    n++;
}
