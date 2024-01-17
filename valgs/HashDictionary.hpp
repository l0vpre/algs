#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include "HashTable.hpp"
#include <cstddef>
#include <optional>

template <typename T, typename THash>
static size_t hashdict_hash_func(T item)
{
    return THash{}(item.key);
}

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

  private:
    HashTable<Pair> *_table;

  public:
    // TODO: move implementation from class definition
    HashDictionary()
    {
        _table = new HashTable<Pair>(&hashdict_hash_func<Pair, THash>);
    }
    // TODO: move implementation from class definition
    ~HashDictionary()
    {
        delete _table;
    }
    // TODO: ifdef VALGS_TESTING
    // TODO: move implementation from class definition
    size_t buckets_count()
    {
        return _table->buckets_count;
    }
    // TODO: move implementation from class definition
    size_t count()
    {
        return _table->count;
    }
    void insert(TKey key, TValue value); // TODO: test insert
    std::optional<TValue> get(TKey key); // TODO: get
    bool contains_key(TKey key);         // TODO: contains_key
    bool remove(TKey key);               // TODO: remove
    // TODO: move implementation from class definition
    size_t hash_index(TKey key)
    {
        return THash{}(key) % _table->buckets_count;
    }
};

template <typename TKey, typename TValue, typename THash>
void HashDictionary<TKey, TValue, THash>::insert(TKey key, TValue value)
{
    if (_table->need_to_expand())
    {
        _table->expand();
    }
    auto bucket = (*_table)[hash_index(key)];
    for (auto &pair : *bucket)
    {
        if (pair.key == key)
        {
            pair.value = value;
            return;
        }
    }
    bucket->add_head(Pair(key, value));
    _table->count++;
}

template <typename TKey, typename TValue, typename THash>
std::optional<TValue> HashDictionary<TKey, TValue, THash>::get(TKey key)
{
    auto bucket = (*_table)[hash_index(key)];
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
    auto bucket = (*_table)[hash_index(key)];
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
    auto bucket = (*_table)[hash_index(key)];
    auto is_removed = bucket->remove_by([&key](Pair pair) { return pair.key == key; });
    if (is_removed)
    {
        _table->count--;
        return true;
    }
    return false;
}

#endif
