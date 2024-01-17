#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "LinkedList.hpp"
#include <cassert>
#include <functional>

template <typename T>
struct HashTable
{
    typedef LinkedList<T> *Bucket;
    typedef std::function<size_t(const T &)> HashFunc;
    static const size_t DEFAULT_BUCKET_COUNT = 16;
    constexpr static const float DEFAULT_GROW_FACTOR = 0.75f;

    Bucket *buckets;
    size_t count;
    size_t buckets_count;
    float grow_factor;

    HashFunc hash_func;

    HashTable(HashFunc func, size_t buckets_count = DEFAULT_BUCKET_COUNT, float grow_factor = DEFAULT_GROW_FACTOR);
    ~HashTable();

    // TODO: move implementation from class definition
    bool need_to_expand()
    {
        return count > buckets_count * grow_factor;
    }
    void expand();
    T *to_array();             // TODO: test to_array
    size_t count_collisions(); // TODO: test count_collisions
    double load();             // TODO: test load
    Bucket operator[](size_t index);
};

template <typename T>
HashTable<T>::HashTable(HashFunc func, size_t buckets_count, float grow_factor)

{
    this->buckets_count = buckets_count;
    this->grow_factor = grow_factor;
    count = 0;
    hash_func = func;

    buckets = new Bucket[buckets_count];
    for (size_t i = 0; i < buckets_count; i++)
    {
        buckets[i] = new LinkedList<T>();
    }
}

template <typename T>
HashTable<T>::~HashTable()
{
    for (size_t i = 0; i < buckets_count; i++)
    {
        delete buckets[i];
    }
    delete[] buckets;
}

template <typename T>
void HashTable<T>::expand()
{
    size_t new_buckets_count = buckets_count * 2;
    LinkedList<T> **new_buckets = new LinkedList<T> *[new_buckets_count];

    for (size_t i = 0; i < new_buckets_count; i++)
    {
        new_buckets[i] = new LinkedList<T>();
    }
    for (size_t i = 0; i < buckets_count; i++)
    {
        for (auto &item : *buckets[i])
        {
            size_t hash = hash_func(item) % new_buckets_count;
            new_buckets[hash]->add_head(item);
        }
    }

    for (size_t i = 0; i < buckets_count; i++)
    {
        delete buckets[i];
    }
    delete[] buckets;

    buckets = new_buckets;
    buckets_count = new_buckets_count;
}

template <typename T>
T *HashTable<T>::to_array()
{
    int capacity = buckets_count + count_collisions();
    T *array = new T[capacity];
    int index = 0;
    for (int i = 0; i < capacity; i++)
    {
        for (auto &elem : *buckets[i])
        {
            array[index] = elem;
            index++;
        }
    }
    return array;
}

template <typename T>
size_t HashTable<T>::count_collisions()
{
    size_t count_collisions = 0;
    for (size_t i = 0; i < buckets_count; i++)
    {
        if (buckets[i]->count() > 1)
        {
            count_collisions += buckets[i]->count() - 1;
        }
    }
    return count_collisions;
}

template <typename T>
double HashTable<T>::load()
{
    double count = 0;
    double sum = 0;
    for (size_t i = 0; i < buckets_count; i++)
    {
        if (buckets[i]->count() >= 1)
        {
            count++;
            sum += buckets[i]->count();
        }
    }
    double res = sum / count;
    return res;
}

template <typename T>
typename HashTable<T>::Bucket HashTable<T>::operator[](size_t index)
{
    assert(index < buckets_count);
    return buckets[index];
}

#endif // HASH_TABLE_H
