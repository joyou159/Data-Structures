#include <iostream>
#include <vector>
typedef std::string Elem;
class NodeList
{
private:
    struct Node // declaration of a node of doubly linked list.
    {
        Elem data;
        Node *next;
        Node *prev;
    };

public:
    class Iterator
    {
    public: // overloaded operators
        Elem &operator*();
        bool operator==(const Iterator &q);
        bool operator!=(const Iterator &p);
        Iterator &operator++();
        Iterator &operator--();
        friend class NodeList;

    private:
        Node *v;
        Iterator(Node *u); // the constructor is private so that only NodeList is allowed to create new iterator objects.
    };

public:
    NodeList();
    int size() const;
    bool empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertBack(const Elem &e);
    void insertFront(const Elem &e);
    void insert(const Iterator &p, const Elem &e);
    void erase(const Iterator &p);
    void eraseBack();
    void eraseFront();
    ~NodeList();
    NodeList(const NodeList &e);
    void operator=(const NodeList &e);

private:
    int n; // size of the List
    Node *header;
    Node *trailer;
};
int main()
{
    NodeList names;
    names.insertFront("youssef");
    names.insertFront("Ahemd");
    std::cout << *(names.begin());
}
NodeList::Iterator::Iterator(Node *u) : v(u) {}
Elem &NodeList::Iterator::operator*()
{

    return v->data;
}

bool NodeList::Iterator::operator==(const Iterator &q)
{
    return v == q.v;
}
bool NodeList::Iterator::operator!=(const Iterator &p)
{
    return v != p.v;
}
NodeList::Iterator &NodeList::Iterator::operator++()
{
    v = v->next;
    return *this;
}
NodeList::Iterator &NodeList::Iterator::operator--()
{
    v = v->prev;
    return *this;
}
NodeList::NodeList()
{
    n = 0;
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}
int NodeList::size() const { return n; }
bool NodeList::empty() const { return n == 0; }
NodeList::Iterator NodeList::begin() const
{
    return Iterator(header->next); // constructor calling
}
NodeList::Iterator NodeList::end() const
{
    return Iterator(trailer);
}
void NodeList::insert(const NodeList::Iterator &p, const Elem &e)
{
    Node *u = new Node;
    u->data = e;
    u->prev = p.v->prev;
    u->next = p.v;
    p.v->prev = u;
    u->prev->next = u;
    n++;
}
void NodeList::insertBack(const Elem &e)
{
    insert(end(), e);
}
void NodeList::insertFront(const Elem &e)
{
    insert(begin(), e);
}
void NodeList::erase(const NodeList::Iterator &p)
{
    p.v->next->prev = p.v->prev;
    p.v->prev->next = p.v->next;
    n--;
    delete p.v;
}
void NodeList::eraseBack()
{
    erase(--end());
}
void NodeList::eraseFront()
{
    erase(begin());
}
NodeList::~NodeList()
{
    while (!empty())
    {
        eraseFront();
    }
    delete header;
    delete trailer;
}
NodeList::NodeList(const NodeList &e) : NodeList()
{

    Iterator temp = e.begin();
    while (temp != e.end())
    {
        insertFront(*temp);
        ++temp;
    }
}
void NodeList::operator=(const NodeList &e)
{
    while (!empty())
    {
        eraseFront();
    }
    Iterator temp = e.begin();
    while (temp != e.end())
    {
        insertFront(*temp);
        ++temp;
    }
}
