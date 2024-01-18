#include <iostream>
#include "exception.h"
template <typename K, typename V>
class Map
{
private:
    class Entry
    {
    public:
        Entry(const K &k = K(), const V &v = V()) : key(k), value(v) {}
        const K &getKey() const { return key; }
        const V &getValue() const { return value; }
        void setKey(const K &k) { key = k; }
        void setValue(const V &v) { value = v; }
        friend class Iterator;
        friend class Map;

    private:
        K key;
        V value;
        Entry *next;
        Entry *prev;
    };

public:
    class Iterator
    {
    public: // overloaded operators
        Entry operator*();
        bool operator==(const Iterator &q);
        bool operator!=(const Iterator &p);
        Iterator &operator++();
        Iterator &operator--();
        friend class Map;
        Iterator(Entry *u);
        Iterator() : v(nullptr) {}

    private:
        Entry *v;
    };

public:
    Map();
    ~Map();
    Map(const Map &e);
    void operator=(const Map &e);
    int size() const;
    bool empty() const;
    Iterator find(const K &k) const;
    Iterator put(const K &k, const V &v);
    void erase(const K &k) throw(NoneExistentEntry);
    void erase(const Iterator &p);
    Iterator begin() const;
    Iterator end() const;

protected:
    Iterator insertBack(const K &k, const V &v);
    void remove(const Iterator &p);

private:
    Entry *header;
    Entry *trailer;
    int n;
};
int main()
{
    Map<int, std::string> names;
    names.put(1, "youssef");
    names.put(2, "Ahmed");
    names.put(3, "Shawki");
    names.put(1, "shehab");
    Map<int, std::string>::Iterator p;
    for (p = names.begin(); p != names.end(); ++p)
    {
        std::cout << (*p).getValue() << " ";
    }
}
template <typename K, typename V>
Map<K, V>::Iterator::Iterator(Entry *u) : v(u) {}
template <typename K, typename V>
typename Map<K, V>::Entry Map<K, V>::Iterator::operator*()
{
    return *v;
}
template <typename K, typename V>
bool Map<K, V>::Iterator::operator==(const Iterator &q)
{
    return v == q.v;
}
template <typename K, typename V>
bool Map<K, V>::Iterator::operator!=(const Iterator &p)
{
    return v != p.v;
}
template <typename K, typename V>
typename Map<K, V>::Iterator &Map<K, V>::Iterator::operator++()
{
    v = v->next;
    return *this;
}
template <typename K, typename V>
typename Map<K, V>::Iterator &Map<K, V>::Iterator::operator--()
{
    v = v->prev;
    return *this;
}
template <typename K, typename V>
Map<K, V>::Map()
{
    header = new Entry;
    trailer = new Entry;
    header->next = trailer;
    trailer->prev = header;
    n = 0;
}
template <typename K, typename V>
Map<K, V>::~Map()
{
    if (!empty())
    {
        remove(begin());
    }
}
template <typename K, typename V>
int Map<K, V>::size() const
{
    return n;
}
template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return n == 0;
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin() const
{
    return Iterator(header->next);
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end() const
{
    return Iterator(trailer);
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K &k) const
{

    for (Iterator p = begin(); p != end(); ++p)
    {
        Entry *temp = p.v;
        if (temp->getKey() == k)
        {
            return p;
        }
    }
    return end();
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::put(const K &k, const V &v)
{

    for (Iterator p = begin(); p != end(); ++p)
    {
        Entry *temp = p.v;
        if (temp->getKey() == k)
        {
            temp->setValue(v);
            return p;
        }
    }
    Iterator p = insertBack(k, v);
    n++;
    return p;
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::insertBack(const K &k, const V &v)
{
    Entry *u = new Entry;
    u->next = trailer;
    u->prev = trailer->prev;
    trailer->prev->next = u;
    trailer->prev = u;
    u->key = k;
    u->value = v;
    return --end();
}
template <typename K, typename V>
void Map<K, V>::remove(const Iterator &p)
{
    Entry *temp = p.v;
    temp->prev = temp->next->prev;
    temp->next->prev = temp->prev;
    delete temp;
}

template <typename K, typename V>
void Map<K, V>::erase(const K &k) throw(NoneExistentEntry)
{
    if (find(k) == end())
    {
        throw NoneExistentEntry("there isn't any entry with such key!");
    }
    else
    {

        for (Iterator p = begin(); p != end(); ++p)
        {
            Entry temp = *p;
            if (temp.key == k)
            {

                remove(p);
                n--;
            }
        }
    }
}
template <typename K, typename V>
Map<K, V>::Map(const Map &e) : Map()
{
    Iterator p;
    for (p = e.begin(); p != e.end(); ++p)
    {
        K temp1 = (*p).getKey();
        V temp2 = (*p).getValue();
        this->put(temp1, temp2);
    }
}
template <typename K, typename V>
void Map<K, V>::operator=(const Map &e)
{
    Iterator p;
    for (p = this->begin; p != this->end(); ++p)
    {
        this->erase(p);
    }

    for (p = e.begin(); p != e.end(); ++p)
    {
        K temp1 = (*p).getKey();
        V temp2 = (*p).getValue();
        this->put(temp1, temp2);
    }
}
