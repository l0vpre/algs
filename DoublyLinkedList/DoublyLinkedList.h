#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <optional>
#include <iterator>

template <typename T>
class DoublyLinkedList
{
    struct Node
    {
        T Data;
        Node *Next;
        Node* Previous;
        Node(T data);
    };

    struct Iterator
    {
        using value_type = T;
        using element_type = T;
        using iterator_category = std::forward_iterator_tag;
    private:
        Node* current;
    public:
    Iterator();
    Iterator(Node* node);
    Iterator(const Iterator& iter);
    Iterator& operator=(const Iterator& other);
    T& operator*();
    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    int operator-(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
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
    void add_tail(Node *new_node);
    void remove(T data);
    void remove_at(int index);

    Iterator begin();
    Iterator begin() const;
    Iterator end();
    Iterator end() const;
};

#endif