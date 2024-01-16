#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <functional>
#include <iterator>
#include <optional>

template <typename T>
class LinkedList
{
    struct Node
    {
        T data;
        Node *next;
        Node(T data) : data(data), next(nullptr){};
    };

    struct Iterator
    {
        using value_type = T;
        using element_type = T;
        using iterator_category = std::forward_iterator_tag;

      private:
        Node *current;

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

  public:
    void delete_all_nodes();
    void add_head(T data);
    int count();
    std::optional<T> head();
    std::optional<T> tail();
    void clear();
    ~LinkedList();
    LinkedList();
    Node *get_node_at(int index);
    std::optional<T> get_at(int index);
    void set_at(int index, T value);
    std::optional<T> pop_head();
    std::optional<T> pop_tail();
    void insert(int index, T data);
    void add_tail(T data);
    bool remove(T data);
    bool remove_at(int index);
    // TODO: add remove_by version accepting predicate that accepts T by value
    bool remove_by(std::function<bool(T &)> predicate);
    bool contains(T item);

    Iterator begin();
    Iterator begin() const;
    Iterator end();
    Iterator end() const;
};

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
    return current->data;
}

template <typename T>
const T &LinkedList<T>::Iterator::operator*() const
{
    return current->data;
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
    current = current->next;
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
int LinkedList<T>::Iterator::operator-(const LinkedList::Iterator &other) const
{
    return 0;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const LinkedList::Iterator &other) const
{
    return current == other.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const LinkedList::Iterator &other) const
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
        _head->next = node;
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
    return _head->data;
}

template <typename T>
std::optional<T> LinkedList<T>::tail()
{
    if (_tail == nullptr)
    {
        return std::nullopt;
    }
    return _tail->data;
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
        current = current->next;
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
    return node->data;
}

template <typename T>
void LinkedList<T>::set_at(int index, T value)
{
    Node *node = get_node_at(index);
    if (node == nullptr)
    {
        return;
    }
    node->data = value;
}

template <typename T>
std::optional<T> LinkedList<T>::pop_head()
{
    if (_head == nullptr)
    {
        return std::nullopt;
    }
    T last_head_data = _head->data;
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
    T last_tail_data = _tail->data;
    if (_count == 1)
    {
        delete _tail;
        _tail = nullptr;
        _head = nullptr;
        _count--;
        return last_tail_data;
    }
    Node *new_tail = _tail->next;
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
        add_tail(new_node);
        return;
    }
    if (index == _count)
    {
        add_head(data);
        return;
    }

    Node *previous_node = get_node_at(index - 1);
    new_node->next = previous_node->next;
    previous_node->next = new_node;

    _count++;
}

template <typename T>
void LinkedList<T>::add_tail(T data)
{
    Node *node = new Node(data);

    if (_count == 0)
    {
        _tail = node;
        _head = node;
    }
    else
    {
        node->next = _tail;
        _tail = node;
    }

    _count++;
}

template <typename T>
bool LinkedList<T>::remove(T data)
{
    if (_head->data == data)
    {
        pop_head();
        return true;
    }
    if (_tail->data == data)
    {
        pop_tail();
        return true;
    }
    Node *current = _tail;

    for (int i = 0; i <= _count - 2; i++)
    {
        Node *previous = current;
        current = current->next;
        if (current->data == data)
        {
            previous->next = current->next;
            delete current;
            _count--;
            return true;
        }
    }
    return false;
}
template <typename T>
bool LinkedList<T>::remove_by(std::function<bool(T &)> predicate)
{
    if (predicate(_head->data))
    {
        pop_head();
        return true;
    }
    if (predicate(_tail->data))
    {
        pop_tail();
        return true;
    }
    Node *current = _tail;
    for (int i = 0; i <= _count - 2; i++)
    {
        Node *previous = current;
        current = current->next;
        if (predicate(current->data))
        {
            previous->next = current->next;
            delete current;
            _count--;
            return true;
        }
    }
    return false;
}

template <typename T>
bool LinkedList<T>::remove_at(int index)
{
    if (index >= _count || index < 0)
    {
        return false;
    }
    if (index == 0)
    {
        pop_tail();
        return true;
    }
    if (index == _count - 1)
    {
        pop_head();
        return true;
    }

    auto previous_des_node = get_node_at(index - 1);
    auto desired_node = previous_des_node->Next;
    previous_des_node->Next = desired_node->Next;
    delete desired_node;
    _count--;
    return true;
}

template <typename T>
void LinkedList<T>::delete_all_nodes()
{
    while (_tail != nullptr)
    {
        Node *next = _tail->next;
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
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
    return Iterator(_tail);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return Iterator();
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
    return Iterator();
}

template <typename T>
bool LinkedList<T>::contains(T item)
{
    auto current = _tail;
    while (current != nullptr)
    {
        if (current->Data == item)
            return true;
        current = current->Next;
    }
    return false;
}

#endif