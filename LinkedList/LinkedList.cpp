#include "LinkedList.h"
#include <optional>
#include <iterator>

template <typename T>
LinkedList<T>::Node::Node(T data)
{
    Data = data;
    Next = nullptr;
}

template <typename T>
LinkedList<T>::Iterator::Iterator()
{
    current = nullptr;
}

template <typename T>
LinkedList<T>::Iterator::Iterator(typename LinkedList<T>::Node *node)
{
    current = node;
}

template <typename T>
LinkedList<T>::Iterator::Iterator(const typename LinkedList<T>::Iterator &iter)
{
    current = iter.current;
}

template <typename T>
T &LinkedList<T>::Iterator::operator*()
{
    return current->Data;
}

template <typename T>
const T &LinkedList<T>::Iterator::operator*()
    const
{
    return current->Data;
}

template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator=(const typename LinkedList<T>::Iterator &other)
{
    new (this) Iterator(other);
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++()
{
    current = current->Next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    auto iter_current = Iterator(*this);
    ++(*this);
    return iter_current;
}

template <typename T>
int LinkedList<T>::Iterator::operator-(const LinkedList::Iterator &other)
    const
{
    return 0;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const LinkedList::Iterator &other)
    const
{
    return current == other.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const LinkedList::Iterator &other)
    const
{
    return current != other.current;
}

template <typename T>
void LinkedList<T>::add_head(T data)
{
    Node *node = new Node(data);

    if (_count == 0)
    {
        _tail = node;
        _head = node;
    }
    else
    {
        _head->Next = node;
        _head = node;
    }
    _count++;
}

template <typename T>
int LinkedList<T>::count()
{
    return _count;
}

template <typename T>
std::optional<T> LinkedList<T>::head()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    return _head->Data;
}

template <typename T>
std::optional<T> LinkedList<T>::tail()
{
    if (_tail == nullptr)
    {
        return std::nullopt;
    }
    return _tail->Data;
}

template <typename T>
void LinkedList<T>::clear()
{
    delete_all_nodes();
    _tail = nullptr;
    _head = nullptr;
    _count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    delete_all_nodes();
}

template <typename T>
LinkedList<T>::LinkedList()
{
    _count = 0;
    _tail = nullptr;
    _head = nullptr;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::get_node_at(int index)
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
std::optional<T> LinkedList<T>::get_at(int index)
{
    Node *node = get_node_at(index);
    if (node == nullptr)
    {
        return std::nullopt;
    }
    return node->Data;
}

template <typename T>
void LinkedList<T>::set_at(int index, T value)
{
    Node *node = get_node_at(index);
    if (node == nullptr)
    {
        return;
    }
    node->Data = value;
}

template <typename T>
std::optional<T> LinkedList<T>::pop_head()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    T last_head_data = _head->Data;
    delete _head;
    if (_count == 1)
    {
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return last_head_data;
    }
    _head = get_node_at(_count - 2);
    _count--;
    return last_head_data;
}

template <typename T>
std::optional<T> LinkedList<T>::pop_tail()
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
void LinkedList<T>::insert(int index, T data)
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
    previous_node->Next = new_node;

    _count++;
}

template <typename T>
void LinkedList<T>::add_tail(T data)
{
    Node *new_node = new Node(data);

    if (_count == 0)
    {
        _tail = new_node;
        _head = new_node;
    }
    else
    {
        new_node->Next = _tail;
        _tail = new_node;
    }

    _count++;
}

template <typename T>
void LinkedList<T>::remove(T data)
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
void LinkedList<T>::remove_at(int index)
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

    auto previous_des_node = get_node_at(index - 1);
    auto desired_node = previous_des_node->Next;
    previous_des_node->Next = desired_node->Next;
    delete desired_node;
    _count--;
}

template <typename T>
void LinkedList<T>::delete_all_nodes()
{
    while (_tail != nullptr)
    {
        Node *next = _tail->Next;
        delete _tail;
        _tail = next;
    }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return Iterator(_tail);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
    const
{
    return Iterator(_tail);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return Iterator();
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
    const
{
    return Iterator();
}

template class LinkedList<int>;
