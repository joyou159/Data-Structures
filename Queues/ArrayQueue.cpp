#include <iostream>
#include "exception.h"
// we are going to implement a queue using array, in particular circular array.
template <typename E>
class ArrQ
{
public:
    ArrQ(int s = 10);
    ~ArrQ();
    int size() const;
    bool empty() const;
    const E &front() const throw(QueueEmpty);
    void dequeue() throw(QueueEmpty);
    void enqueue(const E &e) throw(QueueFull);

private:
    E *s;
    int N;
    int n;
    int f;
    int r;
};
int main()
{
    ArrQ<std::string> names(5);
    names.enqueue("Youssef");
    names.enqueue("Ahmed");
    std::cout << names.front();
    return 0;
}
template <typename E>
ArrQ<E>::ArrQ(int s) : s(new E[s]), N(s), n(0), f(0), r(0) {}
template <typename E>
ArrQ<E>::~ArrQ()
{
    delete[] s;
}
template <typename E>
int ArrQ<E>::size() const
{
    return n;
}
template <typename E>
bool ArrQ<E>::empty() const
{
    return (n == 0);
}
template <typename E>
const E &ArrQ<E>::front() const throw(QueueEmpty)
{
    if (n == 0)
        throw QueueEmpty("the queue is empty!");
    else
    {
        return s[f];
    }
}
template <typename E>
void ArrQ<E>::dequeue() throw(QueueEmpty)
{
    if (n == 0)
        throw QueueEmpty("the queue is empty!");
    else
    {
        f = (f + 1) % N;
        n--;
    }
}
template <typename E>
void ArrQ<E>::enqueue(const E &e) throw(QueueFull)
{
    if (n == N)
    {
        throw QueueFull("the Queue is full!");
    }
    else
    {
        s[r] = e;
        r = (r + 1) % N;
        n++;
    }
}
