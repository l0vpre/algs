#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// TODO: abstract common implementation from singly and doubly linked lists

#include <iterator>
#include <optional>

template <typename T>
class DoublyLinkedList
{
    struct Node
    {
        T Data;
        Node *Next;
        Node *Previous;
        Node(T data);
    };

    struct Iterator
    {
        using value_type = T;
        using element_type = T;
        using iterator_category = std::forward_iterator_tag;

      private:
        Node *current; /*  */
      public:
        Iterator();
        Iterator(Node *node);
        Iterator(const Iterator &iter);
        Iterator &operator=(const Iterator &other);
        T &operator*();
        const T &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        int operator-(const Iterator &other) const;
        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;
    };

  private:
    Node *_tail;
    Node *_head;
    int _count;
    void delete_all_nodes();

  public:
    void add_head(T data);
    int count();
    std::optional<T> head();
    std::optional<T> tail();
    void clear();
    ~DoublyLinkedList();
    DoublyLinkedList();
    Node *get_node_at(int index);
    std::optional<T> get_at(int index);
    void set_at(int index, T value);
    std::optional<T> pop_head();
    std::optional<T> pop_tail();
    void insert(int index, T data);
    void add_tail(T data);
    void remove(T data);
    void remove_at(int index);

    Iterator begin();
    Iterator begin() const;
    Iterator end();
    Iterator end() const;
};

template <typename T>
DoublyLinkedList<T>::Node::Node(T data)
{
    Data = data;
    Next = nullptr;
    Previous = nullptr;
}

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator()
{
    current = nullptr;
}

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(typename DoublyLinkedList<T>::Node *node)
{
    current = node;
}

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(const typename DoublyLinkedList<T>::Iterator &iter)
{
    current = iter.current;
}

template <typename T>
T &DoublyLinkedList<T>::Iterator::operator*()
{
    return current->Data;
}

template <typename T>
const T &DoublyLinkedList<T>::Iterator::operator*() const
{
    return current->Data;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator &DoublyLinkedList<T>::Iterator::operator=(
    const typename DoublyLinkedList<T>::Iterator &other)
{
    new (this) Iterator(other);
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator &DoublyLinkedList<T>::Iterator::operator++()
{
    current = current->Next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int)
{
    auto iter_current = Iterator(*this);
    ++(*this);
    return iter_current;
}

template <typename T>
int DoublyLinkedList<T>::Iterator::operator-(const DoublyLinkedList::Iterator &other) const
{
    return 0;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const DoublyLinkedList::Iterator &other) const
{
    return current == other.current;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const DoublyLinkedList::Iterator &other) const
{
    return current != other.current;
}

template <typename T>
void DoublyLinkedList<T>::add_head(T data)
{
    Node *node = new Node(data);

    if (_count == 0)
    {
        _tail = node;
        _head = node;
    }
    else
    {
        node->Previous = _head;
        _head->Next = node;
        _head = node;
    }
    _count++;
}

template <typename T>
int DoublyLinkedList<T>::count()
{
    return _count;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::head()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    return _head->Data;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::tail()
{
    if (_tail == nullptr)
    {
        return std::nullopt;
    }
    return _tail->Data;
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    delete_all_nodes();
    _tail = nullptr;
    _head = nullptr;
    _count = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    delete_all_nodes();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    _count = 0;
    _tail = nullptr;
    _head = nullptr;
}

template <typename T>
typename DoublyLinkedList<T>::Node *DoublyLinkedList<T>::get_node_at(int index)
{
    if (index >= _count || index < 0)
    {
        return nullptr;
    }
    Node *current = _tail;
    for (int i = 0; i < index; i++)
    {
        current = current->Next;
    }
    return current;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::get_at(int index)
{
    Node *node = get_node_at(index);
    if (node == nullptr)
    {
        return std::nullopt;
    }
    return node->Data;
}

template <typename T>
void DoublyLinkedList<T>::set_at(int index, T value)
{
    Node *node = get_node_at(index);
    if (node == nullptr)
    {
        return;
    }
    node->Data = value;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::pop_head()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }

    T last_head_data = _head->Data;
    if (_count == 1)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return last_head_data;
    }
    Node *new_head = _head->Previous;
    delete _head;
    _head = new_head;
    _count--;
    return last_head_data;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::pop_tail()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }

    T last_tail_data = _tail->Data;
    if (_count == 1)
    {
        delete _tail;
        _tail = nullptr;
        _head = nullptr;
        _count--;
        return last_tail_data;
    }
    Node *new_tail = _tail->Next;
    delete _tail;
    _tail = new_tail;
    _count--;
    return last_tail_data;
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data)
{
    Node *new_node = new Node(data);

    if (index == 0)
    {
        add_tail(data);
        return;
    }
    if (index == _count)
    {
        add_head(data);
        return;
    }
    Node *previous_node = get_node_at(index - 1);
    new_node->Next = previous_node->Next;
    new_node->Previous = previous_node;
    _count++;
}

template <typename T>
void DoublyLinkedList<T>::add_tail(T data)
{
    Node *new_node = new Node(data);

    if (_count == 0)
    {
        _tail = new_node;
        _head = new_node;
    }
    else
    {
        _tail->Previous = new_node;
        new_node->Next = _tail;
        _tail = new_node;
    }
    _count++;
}

template <typename T>
void DoublyLinkedList<T>::remove(T data)
{
    if (_head->Data == data)
    {
        pop_head();
        return;
    }
    if (_tail->Data == data)
    {
        pop_tail();
        return;
    }
    Node *current = _tail;
    for (int i = 0; i <= _count - 2; i++)
    {
        Node *previous = current;
        current = current->Next;
        if (current->Data == data)
        {
            previous->Next = current->Next;
            delete current;
            _count--;
            return;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::remove_at(int index)
{
    if (index >= _count || index < 0)
    {
        return;
    }
    if (index == 0)
    {
        pop_tail();
        return;
    }
    if (index == _count - 1)
    {
        pop_head();
        return;
    }

    auto desired_node = get_node_at(index);
    auto previous_des_node = desired_node->Previous;
    auto next_des_node = desired_node->Next;
    next_des_node->Previous = previous_des_node;
    previous_des_node->Next = desired_node->Next;
    delete desired_node;
    _count--;
}

template <typename T>
void DoublyLinkedList<T>::delete_all_nodes()
{
    while (_tail != nullptr)
    {
        Node *next = _tail->Next;
        delete _tail;
        _tail = next;
    }
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin()
{
    return Iterator(_tail);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const
{
    return Iterator(_tail);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end()
{
    return Iterator();
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const
{
    return Iterator();
}

#endif // DOUBLY_LINKED_LIST_H
