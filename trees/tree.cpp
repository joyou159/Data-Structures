#include <iostream>
#include <list>
typedef int Elem;
class LinkedBinaryTree
{
protected:
    struct Node
    {
        Elem data;
        Node *par;
        Node *left;
        Node *right;
        Node() : par(nullptr), left(nullptr), right(nullptr) {} // constructor
    };

public:
    class Position
    {
    private:
        Node *v;

    public:
        Position(Node *ptr = nullptr) : v(ptr) {} // constructor
        Elem &operator*()
        {
            return v->data;
        }
        Position left() const
        {
            return Position(v->left);
        }
        Position right() const
        {
            return Position(v->right);
        }
        Position parent() const
        {
            return Position(v->par);
        }
        bool isRoot() const
        {
            return v->par == nullptr;
        }
        bool isExternal() const
        {
            return v->left == nullptr && v->right == nullptr;
        }
        friend class LinkedBinaryTree; // we have to declare the LinkedBinaryTree to be friend of such class to give it the accessability to its private members
    };
    typedef std::list<Position> PositionList;

public: // starting from here we declare the member function of the LinkedBinaryTree
    LinkedBinaryTree();
    int size() const;
    bool empty() const;
    Position root() const;
    PositionList positions() const;
    void addRoot();
    void expandExternal(const Position &p);
    Position removeAboveExternal(const Position &p);

protected:
    void preorder(Node *ptr, PositionList &list) const;

private:
    int n;
    Node *_root;
};
LinkedBinaryTree::LinkedBinaryTree() : n(0), _root(nullptr) {}
int LinkedBinaryTree::size() const
{
    return n;
}
bool LinkedBinaryTree::empty() const
{
    return size() == 0;
}

LinkedBinaryTree::Position LinkedBinaryTree::root() const
{
    return Position(_root);
}
void LinkedBinaryTree::addRoot()
{
    n = 1;
    _root = new Node;
}
void LinkedBinaryTree::expandExternal(const Position &p)
{
    Node *v = p.v; // this is valid as the two classes are friends from just one side
    v->left = new Node;
    v->right = new Node;
    v->left->par = v;
    v->right->par = v;
    n += 2;
}
LinkedBinaryTree::Position LinkedBinaryTree::removeAboveExternal(const Position &p)
{
    Node *v = p.v;
    Node *w = v->par;
    Node *sib = (w->left == v ? w->right : w->left);
    if (w == _root)
    {
        _root = sib;
        sib->par = nullptr;
    }
    else
    {
        Node *gpar = w->par;
        if (w = gpar->left)
        {
            gpar->left = sib;
        }
        else
        {
            gpar->right = sib;
        }
        sib->par = gpar;
    }
    delete v;
    delete w;
    n -= 2;
    return Position(sib);
}
void LinkedBinaryTree::preorder(Node *ptr, PositionList &pl) const
{
    pl.push_back(Position(ptr));
    if (ptr->left != nullptr)
        preorder(ptr->left, pl);
    if (ptr->right != nullptr)
        preorder(ptr->right, pl);
}
LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const
{
    PositionList pl;
    preorder(_root, pl);
    return PositionList(pl); // we are calling the constructor of the STL list.
}
