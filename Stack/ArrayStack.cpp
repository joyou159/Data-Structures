#include <iostream>
#include "exception.h"
#include <vector>
template <typename N>
void printVector(std::vector<N> &v);
template <typename N>
void reverse(std::vector<N> &v);
template <typename E>
class Stack
{
public:
    int size() const;
    const E &top() const throw(StackEmpty);
    void push(const E &e);
    void pop() throw(StackEmpty);
};
template <typename E>
class ArrayStack
{
    enum
    {
        DEFAULT_CAPACITY = 100
    };

public:
    ArrayStack(int cap = DEFAULT_CAPACITY);
    ~ArrayStack();
    ArrayStack(ArrayStack &e);
    void operator=(ArrayStack &e);
    int size() const;
    bool empty() const;
    const E &top() const throw(StackEmpty);
    void push(const E &e) throw(StackFull);
    void pop() throw(StackEmpty);

private:
    E *s;
    int capacity;
    int t; // index of the top of the stack
};
int main()
{
    std::vector<std::string> names = {"Youssef", "Ahmed", "Shawki"};
    printVector(names);
    reverse(names);
    printVector(names);
    return 0;
}
template <typename E>
ArrayStack<E>::ArrayStack(int cap) : s(new E[cap]), capacity(cap), t(-1) {}
template <typename E>
ArrayStack<E>::~ArrayStack()
{
    delete s;
}
template <typename E>
void ArrayStack<E>::operator=(ArrayStack &e)
{
    delete[] s;
    capacity = e.capacity;
    s = new E[capacity];
    for (int i = 0; i < e.size(); i++)
    {
        s[i] = e.s[i];
    }
    t = e.t;
}
template <typename E>
int ArrayStack<E>::size() const
{
    return (t + 1);
}
template <typename E>
bool ArrayStack<E>::empty() const
{
    return (t < 0);
}
template <typename E>
const E &ArrayStack<E>::top() const throw(StackEmpty)
{
    if (empty())
    {
        throw StackEmpty("the stack is empty!");
    }
    else
    {
        return s[t];
    }
}
template <typename E>
void ArrayStack<E>::push(const E &e) throw(StackFull)
{
    if (size() == capacity)
    {
        throw StackFull("the stack is full!");
    }
    else
    {

        s[++t] = e;
    }
}
template <typename E>
void ArrayStack<E>::pop() throw(StackEmpty)
{
    if (empty())
    {
        throw StackEmpty("the stack is empty!");
    }
    else
    {
        t--;
    }
}
template <typename E>
ArrayStack<E>::ArrayStack(ArrayStack &e)
{
    capacity = e.capacity;
    s = new E[capacity];
    for (int i = 0; i < e.size(); i++)
    {
        s[i] = e.s[i];
    }
    t = e.t;
}
template <typename N>
void reverse(std::vector<N> &v)
{
    int size = v.size();
    ArrayStack<N> temp(size);
    for (int i = 0; i < size; i++)
    {
        temp.push(v[i]);
    }
    for (int i = 0; i < size; i++)
    {
        v[i] = temp.top();
        temp.pop();
    }
}
template <typename N>
void printVector(std::vector<N> &v)
{
    int size = v.size();
    std::cout
        << "{ ";
    for (int i = 0; i < size; i++)
    {
        std::cout << v[i];
        if (!(i == size - 1))
        {
            std::cout << " , ";
        }
    }
    std::cout << " }" << std::endl;
}
