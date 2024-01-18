#include <iostream>
class RuntimeException
{
private:
    std::string message;

public:
    RuntimeException(const std::string &error) { message = error; }
    std::string &getMessage()
    {
        return message;
    }
};
class EmptyList : public RuntimeException
{
public:
    EmptyList(std::string e) : RuntimeException(e) {}
};
template <typename E>
class SLinkedList;

template <typename E>
class SNode
{
    E data;
    SNode<E> *next;
    friend class SLinkedList;
};
template <typename E>
class SLinkedList
{
public:
    SLinkedList();
    ~SLinkedList();
    const E &front() const;
    bool empty();
    void AddToFront(const E &e);
    void removeFront();

private:
    SNode<E> *head;
};

int main()
{
    SLinkedList<int> age;
    age.AddToFront(20);
    age.AddToFront(21);
    age.AddToFront(30);
}
template <typename E> // the template specifer must be inserted before any member function definition.
SLinkedList<E>::SLinkedList() : head(nullptr)
{
}
template <typename E>
SLinkedList<E>::~SLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
}
template <typename E>
const E &SLinkedList<E>::front() const
{
    return (head->data);
}
template <typename E>
bool SLinkedList<E>::empty()
{
    return (head == nullptr);
}
template <typename E>
void SLinkedList<E>::AddToFront(const E &e)
{
    SNode<E> *v = new SNode<E>;
    v->data = e;
    v->next = head;
    head = v;
}
template <typename E>
void SLinkedList<E>::removeFront()
{
    SNode<E> *old = head;
    head = old->next;
    delete old;
}
