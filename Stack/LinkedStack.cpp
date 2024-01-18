#include "LinkedList.cpp"
#include <iostream>
#include "exception.h"
#include <vector>
#include <string>
std::vector<std::string> getHtmlTags();
bool isHtmlMatched(std::vector<std::string> e);
bool check(std::string e);
template <typename N>
class LinkedStack
{
public:
    LinkedStack();
    int size() const;
    bool empty() const;
    const N &top() const throw(StackEmpty);
    void push(const N &e);
    void pop() throw(StackEmpty);

private:
    SLinkedList<N> s;
    int n; // Because we don't have a way to know the size of the linked list except by counting the number of node we push.
};
int main()
{
    if (isHtmlMatched(getHtmlTags()))
        std::cout << "the input file is a matched HTML document" << std::endl;
    else
        std::cout << "the input file is not a matched HTML document" << std::endl;
}
template <typename N>
LinkedStack<N>::LinkedStack() : n(0) {}
template <typename N>
int LinkedStack<N>::size() const
{
    return n;
}
template <typename N>
bool LinkedStack<N>::empty() const
{
    return s.empty(); // you have to make sure that empty() method does not change s under any condition
}
template <typename N>
const N &LinkedStack<N>::top() const throw(StackEmpty)
{
    if (empty())
    {
        throw StackEmpty("the stack is empty!");
    }
    else
        return s.front();
}
template <typename N>
void LinkedStack<N>::push(const N &e)
{
    s.AddToFront(e);
    n++;
}
template <typename N>
void LinkedStack<N>::pop() throw(StackEmpty)
{
    if (empty())
    {
        throw StackEmpty("the stack is empty");
    }
    else
    {
        s.removeFront();
        n--;
    }
}
bool check(std::string e)
{
    int size = e.length();
    LinkedStack<char> expr;
    for (int i = 0; i < size; i++)
    {
        if (e[i] == '(' || e[i] == '{' || e[i] == '[')
        {
            expr.push(e[i]);
        }
        else if (e[i] == ')' || e[i] == '}' || e[i] == ']')
        {
            if (expr.empty())
            {
                return false;
            }
            else if ((expr.top() == '(' && e[i] == ')') ||
                     (expr.top() == '[' && e[i] == ']') || (expr.top() == '{' && e[i] == '}'))
            {
                expr.pop();
            }
            else
            {
                return false;
            }
        }
    }
    if (expr.empty())
    {
        return true;
    }
    else
        return false;
}
std::vector<std::string> getHtmlTags()
{
    std::vector<std::string> tags;
    while (std::cin)
    {
        std::string line;
        getline(std::cin, line);
        int pos = 0;
        int ts = line.find("<", pos);        // there is an implicit casting occurs here.
        while (ts != int(std::string::npos)) // which means repeat until the end of the string.
        {
            int te = line.find(">", ts + 1);
            tags.push_back(line.substr(ts, (te - ts + 1)));
            pos = 1 + te;
            ts = line.find("<", pos);
        }
    }
    return tags;
}
bool isHtmlMatched(std::vector<std::string> e)
{
    LinkedStack<std::string> temp;
    typedef std::vector<std::string>::const_iterator Iter; // iterator object type
    for (Iter p = e.begin(); p != e.end(); p++)            // the iterator is like pointer which points to an element inside a container
    {
        if (p->at(1) != '/')
            temp.push(*p);

        else
        {
            if (temp.empty())
            {
                return false;
            }
            std::string open = temp.top().substr(1);
            std::string close = p->substr(2);
            if (open.compare(close) != 0) // compare method return 0 if the two strings are equal.
            {
                return false;
            }
            else
            {
                temp.pop();
            }
        }
    }
    if (temp.empty())
        return true;
    else
        return false;
}