#include "LinkedList.h"
#include <iostream>

template <typename T, typename THash>
class HashSet
{
  private:
    LinkedList<T> **_buckets;
    size_t _count;
    size_t _buckets_count;
    const float _GROW_FACTOR = 0.75;

  public:
    HashSet();
    size_t buckets_count();
    size_t count();
    void add(T item);
    bool contains(T item);
    bool remove(T Item);
    void expand();
    ~HashSet();
    void delete_all_backet();
    T *to_array();
    size_t count_collisions();
    double load();
};

template <typename T, typename THash>
HashSet<T, THash>::HashSet()
{
    _count = 0;
    _buckets_count = 16;
    _buckets = new LinkedList<T> *[_buckets_count];
    for (size_t i = 0; i < _buckets_count; i++)
    {
        _buckets[i] = new LinkedList<T>();
    }
}

template <typename T, typename THash>
size_t HashSet<T, THash>::buckets_count()
{
    return _buckets_count;
}

template <typename T, typename THash>
size_t HashSet<T, THash>::count()
{
    return _count;
}

template <typename T, typename THash>
void HashSet<T, THash>::add(T item)
{
    size_t hash = THash{}(item) % _buckets_count;
    if (_buckets[hash]->contains(item))
    {
        return;
    }
    if (_count >= _buckets_count * _GROW_FACTOR)
    {
        expand();
    }
    _buckets[hash]->add_head(item);
    _count++;
}

template <typename T, typename THash>
void HashSet<T, THash>::expand()
{
    size_t new_buckets_count = _buckets_count * 2;
    LinkedList<T> **new_buckets = new LinkedList<T> *[new_buckets_count];

    for (size_t i = 0; i < new_buckets_count; i++)
    {
        new_buckets[i] = new LinkedList<T>();
    }
    for (size_t i = 0; i < _buckets_count; i++)
    {
        for (auto &item : *_buckets[i])
        {
            size_t hash = THash{}(item) % new_buckets_count;
            new_buckets[hash]->add_head(item);
        }
    }

    for (size_t i = 0; i < _buckets_count; i++)
    {
        delete _buckets[i];
    }
    delete[] _buckets;
    _buckets = new_buckets;
    _buckets_count = new_buckets_count;
}

template <typename T, typename THash>
bool HashSet<T, THash>::contains(T item)
{
    size_t hash = THash{}(item) % _buckets_count;
    return _buckets[hash]->contains(item);
}

template <typename T, typename THash>
bool HashSet<T, THash>::remove(T item)
{
    size_t hash = THash{}(item) % _buckets_count;
    auto is_removed = _buckets[hash]->remove(item);
    if (is_removed)
    {
        _count--;
        return true;
    }
    return false;
}

template <typename T, typename THash>
HashSet<T, THash>::~HashSet()
{
    delete_all_backet();
    delete[] _buckets;
}

template <typename T, typename THash>
void HashSet<T, THash>::delete_all_backet()
{
    for (size_t i = 0; i < _buckets_count; i++)
    {
        delete _buckets[i];
    }
}

template <typename T, typename THash>
size_t HashSet<T, THash>::count_collisions()
{
    size_t count_collisions = 0;
    for (size_t i = 0; i < _buckets_count; i++)
    {
        if (_buckets[i]->count() > 1)
        {
            count_collisions += _buckets[i]->count() - 1;
        }
    }
    return count_collisions;
}

template <typename T, typename THash>
T *HashSet<T, THash>::to_array()
{
    int capacity = _buckets_count + count_collisions();
    T *array = new T[capacity];
    int index = 0;
    for (int i = 0; i < capacity; i++)
    {
        for (auto &elem : *_buckets[i])
        {
            array[index] = elem;
            index++;
        }
    }
    return array;
}

template <typename T, typename THash>
double HashSet<T, THash>::load()
{
    double count = 0;
    double sum = 0;
    for (size_t i = 0; i < _buckets_count; i++)
    {
        if (_buckets[i]->count() >= 1)
        {
            count++;
            sum += _buckets[i]->count();
        }
    }
    double res = sum / count;
    return res;
}
