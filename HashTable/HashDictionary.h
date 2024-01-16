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
    size_t count_collisions();
    double load();
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
}

template <typename TKey, typename TValue, typename THash>
void HashDictionary<TKey, TValue, THash>::expand()
{
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
#endif