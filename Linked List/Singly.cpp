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
class StringNode
{
    std::string data;
    StringNode *next;
    friend class StringLinkedList; // we have defined StringLinkedList class as a friend to StringNode so that we can access its private members
};
class StringLinkedList
{
public:
    StringLinkedList();
    ~StringLinkedList();
    bool empty();
    const std::string &front() const; // such method returns a const string meaning that we can not modfiy it.
    void addToFront(const std::string &e);
    void removeFront() throw(EmptyList);

private:
    StringNode *head;
};
int main()
{
    StringLinkedList names;
    names.addToFront("youssef Ahmed");
    names.addToFront("Mohamed");
    names.addToFront("Ahmed");
    StringLinkedList N;
    N = names;
    std::cout << N.empty() << std::endl;
    std::cout << N.front();
}
StringLinkedList::StringLinkedList() : head(nullptr) {}
StringLinkedList::~StringLinkedList()
{
    while (!empty())
    {
        removeFront();
    }
}
bool StringLinkedList::empty()
{
    return (head == nullptr);
}
const std::string &StringLinkedList::front() const
{
    return head->data;
}
void StringLinkedList::addToFront(const std::string &e)
{
    StringNode *extra = new StringNode;
    extra->data = e;
    extra->next = head;
    head = extra;
}
void StringLinkedList::removeFront() throw(EmptyList)
{
    if (head == nullptr)
    {
        throw EmptyList("the list is empty");
    }
    else
    {
        StringNode *old = head;
        head = old->next;
        delete old;
    }
}
