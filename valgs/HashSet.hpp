#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include "HashTable.hpp"

template <typename T, typename THash>
static size_t hashset_hash_func(T item)
{
    return THash{}(item);
}

template <typename T, typename THash = std::hash<T>>
class HashSet
{
  private:
    HashTable<T> _table;

  public:
    // TODO: move implementation from class definition
    HashSet() : _table(&hashset_hash_func<T, THash>)
    {
    }

    // TODO: move implementation from class definition

    // TODO: make all needed testing methods
#ifdef VALGS_TESTING
    // TODO: move implementation from class definition
    size_t buckets_count()
    {
        return _table.buckets_count;
    };
    // TODO: move implementation from class definition
    HashTable<T> *get_table()
    {
        return _table;
    }
#endif // VALGS_TESTING
    // TODO: move implementation from class definition
    size_t count()
    {
        return _table.count;
    };
    void add(T item);      // TODO: test add
    bool contains(T item); // TODO: test contains
    bool remove(T Item);   // TODO: test remove
    // TODO: to_array
    // TODO: move implementation from class definition
    size_t hash_index(T &item)
    {
        return THash{}(item) % _table.buckets_count;
    }
};

template <typename T, typename THash>
void HashSet<T, THash>::add(T item)
{
    if (_table.need_to_expand())
    {
        _table.expand();
    }

    size_t hash = hash_index(item);
    auto bucket = _table[hash];

    if (bucket->contains(item))
    {
        return;
    }
    bucket->add_head(item);
    _table.count++;
}

template <typename T, typename THash>
bool HashSet<T, THash>::contains(T item)
{
    size_t hash = hash_index(item);
    return _table[hash]->contains(item);
}

template <typename T, typename THash>
bool HashSet<T, THash>::remove(T item)
{
    size_t hash = hash_index();
    auto bucket = _table[hash];

    auto is_removed = bucket->remove(item);
    if (is_removed)
    {
        _table.count--;
        return true;
    }
    return false;
}

#endif // HASH_SET_HPP
