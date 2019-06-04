#ifndef ALG_SORT_LINKEDLIST_H
#define ALG_SORT_LINKEDLIST_H

#include <iostream>
#include <cstdio>
#include <vector>

template<typename T>
class LinkedList
{
public:
    struct Node
    {
        friend class LinkedList;

    public:
        explicit Node(const T& val = T(), Node* prev = nullptr, Node* next = nullptr)
                : _value(val), _prev(prev), _next(next)
        {
        }

        const T& getValue() const
        {
            return _value;
        }

        void setValue(const T& val)
        {
            _value = val;
        }

        const Node* getNext() const
        {
            return _next;
        }

        Node* getNext()
        {
            return _next;
        }

        void setNext(Node* next)
        {
            _next = next;
        }

        const Node* getPrev() const
        {
            return _prev;
        }

        Node* getPrev()
        {
            return _prev;
        }

        void setPrev(Node* prev)
        {
            _prev = prev;
        }

    protected:
        Node* _prev;
        Node* _next;
        T _value;

    };

public:

    LinkedList() : _head(nullptr), _tail(nullptr), _size(0)
    {
    }

    ~LinkedList()
    {
        while (_head)
        {
            Node* next = _head->_next;
            delete _head;
            --_size;
            _head = next;
        }
    }

    LinkedList(const LinkedList<T>& other) :
            _head(nullptr), _tail(nullptr), _size(0)
    {
        *this = other;
    }

    LinkedList& operator=(const LinkedList<T>& other)
    {
        if (other._head)
        {
            Node* current = other._head;
            while (current)
            {
                Node* newNode = new Node(*current);
                appendNodeAsTail(newNode);
                ++_size;
                current = current->_next;
            }

        }
        return *this;
    }

    Node* getHead() const
    {
        return _head;
    }

    void setHead(Node* head)
    {
        _head = head;
    }

    size_t getSize() const
    {
        return _size;
    }

    Node* getTail()
    {
        return _tail;
    }

    const Node* getTail() const
    {
        return _tail;
    }

    Node* insertNodeBefore(Node* newel, Node* nextel = nullptr)
    {
        if (!newel)
            throw;
        if (_size == 0 || !nextel)
            appendNodeAsHead(newel);
        else
        {
            newel->_next = nextel;
            nextel->_prev->_next = newel;
            nextel->_prev = newel;
            ++_size;

        }
        return newel;
    }

    Node* insertValueBefore(const T& val, Node* nextel = nullptr)
    {
        Node* newnode = new Node(val);
        return insertNodeBefore(newnode, nextel);
    }

    Node* insertNodeAfter(Node* newel, Node* pr = nullptr)
    {
        if (!newel)
            throw;
        if (_size == 0 || !pr)
            appendNodeAsTail(newel);
        else
        {
            newel->_next = pr->_next;
            pr->_next = newel;
            newel->_prev = pr;
            if (newel->_next)
                newel->_next->_prev = newel;
            ++_size;
        }
        return newel;
    }

    Node* insertValAfter(const T& val, Node* pr = nullptr)
    {
        Node* newnode = new Node(val);
        return insertNodeAfter(newnode, pr);
    }

    Node* appendNodeAsHead(Node* newel)
    {
        if (!newel)
            throw;
        if (!_size)
        {
            _head = newel;
            _tail = _head;
            ++_size;
        }
        else
        {
            _head->_prev = newel;
            newel->_next = _head;
            _head = newel;
            ++_size;
        }
        return newel;
    }

    Node* appendValueAsHead(const T& val)
    {
        Node* newNd = new Node(val);
        return appendNodeAsHead(newNd);
    }

    Node* appendNodeAsTail(Node* newel)
    {
        if (!newel)
            throw;
        if (!_size)
        {
            _head = newel;
            _tail = _head;
            ++_size;
        }
        else
        {
            _tail->_next = newel;
            newel->_prev = _tail;
            _tail = newel;
            ++_size;
        }
        return newel;
    }

    Node* appendValueAsTail(const T& val)
    {
        Node* newel = new Node(val);
        return appendNodeAsTail(newel);
    }


protected:
    Node* _head;
    Node* _tail;
    size_t _size;
};


#endif //ALG_SORT_LINKEDLIST_H
