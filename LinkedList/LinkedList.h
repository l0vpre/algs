#ifndef LINKED_LIST_H
#define LINKED_LIST_H
template <typename T>
class LinkedList
{
    struct Node
    {
        T Data;
        Node *Next;
        Node(T data)
        {
            Data = data;
            Next = nullptr;
        }
    };

private:
    Node *_tail;
    Node *_head;
    int _count;
    void delete_all_nodes()
    {
        while (_tail != nullptr)
        {
            Node *next = _tail->Next;
            delete _tail;
            _tail = next;
        }
    }

public:
    void add(T data)
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
    int count()
    {
        return _count;
    }

    std::optional<T> head()
    {
        if (_head == nullptr)
        {
            return std::nullopt;
        }
        return _head->Data;
    }

    std::optional<T> tail()
    {
        if (_tail == nullptr)
        {
            return std::nullopt;
        }
        return _tail->Data;
    }

    void clear()
    {
        delete_all_nodes();
        _tail = nullptr;
        _head = nullptr;
        _count = 0;
    }
    ~LinkedList()
    {
        delete_all_nodes();
        printf("был вызван деструкутор\n");
        std::cout << "Destructor\n";
    }
    LinkedList()
    {
        _count = 0;
        _tail = nullptr;
        _head = nullptr;
    }
    Node* get_node_at(int index)
    {
        if (index >= _count)
        {
            return nullptr;
        }
        Node* current = _tail;
        for (int i = 0; i < index; i++)
        {
            current = current->Next;
        }
        return current;
    }
    std::optional<T> get_at(int index)
    {
        Node* node = get_node_at(index);
        if(node == nullptr)
        {
            return std::nullopt;
        }
        return node->Data; 
    }

    void set_at(int index, T value)
    {
        Node* node = get_node_at(index);
        if(node == nullptr)
        {
            return;
        }
        node->Data = value;

    }

};
#endif 