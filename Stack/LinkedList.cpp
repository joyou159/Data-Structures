template <typename E>
class SLinkedList;

template <typename E>
class SNode
{
    E data;
    SNode<E> *next;
    friend class SLinkedList<E>;
};
template <typename E>
class SLinkedList
{
public:
    SLinkedList();
    ~SLinkedList();
    const E &front() const;
    bool empty() const;
    void AddToFront(const E &e);
    void removeFront();

private:
    SNode<E> *head;
};

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
bool SLinkedList<E>::empty() const
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