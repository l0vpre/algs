#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H
#include "LinkedList.h"
#include <cstddef>
#include <iostream>
#include <optional>

template <typename TKey, typename TValue, typename THash>
class HashDictionary
{
    struct Pair
    {
        TKey key;
        TValue value;
        Pair(TKey key, TValue value) : key(key), value(value)
        {
        }
    };
    typedef LinkedList<Pair> *Bucket;

  private:
    Bucket *_buckets;
    size_t _count;
    size_t _buckets_count;
    const float _GROW_FACTOR = 0.75;

  public:
    size_t buckets_count()
    {
        return _buckets_count;
    }
    size_t count()
    {
        return _count;
    }
    HashDictionary();
    ~HashDictionary();
    void insert(TKey key, TValue value);
    void expand();
    std::optional<TValue> get(TKey key);
    bool contains_key(TKey key);
    bool remove(TKey key);
};

template <typename TKey, typename TValue, typename THash>
HashDictionary<TKey, TValue, THash>::HashDictionary()
{
    _count = 0;
    _buckets_count = 16;
    _buckets = new LinkedList<Pair> *[_buckets_count];
    for (size_t i = 0; i < _buckets_count; i++)
    {
        _buckets[i] = new LinkedList<Pair>();
    }
}

template <typename TKey, typename TValue, typename THash>
HashDictionary<TKey, TValue, THash>::~HashDictionary()
{
    for (size_t i = 0; i < _buckets_count; i++)
    {
        delete _buckets[i];
    }
    delete[] _buckets;
}

template <typename TKey, typename TValue, typename THash>
void HashDictionary<TKey, TValue, THash>::insert(TKey key, TValue value)
{
    if (_count <= _buckets_count * _GROW_FACTOR)
    {
        expand();
    }
    Bucket bucket = _buckets[THash{}(key) % _buckets_count];
    for (auto &pair : *bucket)
    {
        if (pair.key == key)
        {
            pair.value = value;
            return;
        }
    }
    bucket->add_head(Pair(key, value));
    _count++;
}

template <typename TKey, typename TValue, typename THash>
void HashDictionary<TKey, TValue, THash>::expand()
{
    size_t new_buckets_count = _buckets_count * 2;
    LinkedList<Pair> **new_buckets = new LinkedList<Pair> *[new_buckets_count];
    for (size_t i = 0; i < new_buckets_count; i++)
    {
        new_buckets[i] = new LinkedList<Pair>();
    }

    for (size_t i = 0; i < _buckets_count; i++)
    {
        for (auto &pair : *_buckets[i])
        {
            size_t hash = THash{}(pair.key) % new_buckets_count;
            new_buckets[hash]->add_head(pair);
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

template <typename TKey, typename TValue, typename THash>
std::optional<TValue> HashDictionary<TKey, TValue, THash>::get(TKey key)
{
    Bucket bucket = _buckets[THash{}(key) % _buckets_count];
    for (auto &pair : *bucket)
    {
        if (pair.key == key)
        {
            return pair.value;
        }
    }
    return std::nullopt;
}

template <typename TKey, typename TValue, typename THash>
bool HashDictionary<TKey, TValue, THash>::contains_key(TKey key)
{
    Bucket bucket = _buckets[THash{}(key) % _buckets_count];
    for (auto &pair : *bucket)
    {
        if (pair.key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename TKey, typename TValue, typename THash>
bool HashDictionary<TKey, TValue, THash>::remove(TKey key)
{
    Bucket bucket = _buckets[THash{}(key) % _buckets_count];
    auto is_removed = bucket->remove_by([&key](Pair pair) { return pair.key == key; });
    if (is_removed)
    {
        _count--;
        return true;
    }
    return false;
}

#endif