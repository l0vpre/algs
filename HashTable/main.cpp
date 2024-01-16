#include "HashDictionary.h"
#include "HashSet.h"
#include "LinkedList.h"
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <memory>
#include <vector>

template <typename T, typename THash>
void test_set(std::vector<T> *vec, HashSet<T, THash> *set);

int main()
{
    struct Hash
    {
      public:
        size_t operator()(const std::string &s)
        {
            size_t hash = 0;
            for (size_t i = 0; i < s.length(); i++)
            {
                hash += s[i] * 2861;
                hash = (hash << 16) ^ hash;
                hash = (hash ^ (hash >> 24));
            }

            return hash;
        }
    };
    struct Djb2Hash
    {
      public:
        size_t operator()(const std::string &s)
        {
            size_t hash = 5381;
            for (char c : s)
            {
                hash = ((hash << 5) + hash) + c;
            }

            return hash;
        }
    };

    auto hash_set = std::make_unique<HashSet<int, Hash>>();
    auto hash_dict = std::make_unique<HashDictionary<std::string, size_t, Hash>>();
    std::ifstream fin("words.txt");
    std::string temp;
    size_t num = 0;
    size_t max_count = 100;
    size_t count = 0;
    while (count < max_count && fin >> temp)
    {
        hash_dict->insert(temp, num);
        num += 5;
    }
    printf("%lu\n", hash_dict->get("accept").value());
}

template <typename T, typename THash>
void test_set(std::vector<T> *vec, HashSet<T, THash> *set)
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    for (const T &item : *vec)
    {
        set->add(item);
    }
    auto end = high_resolution_clock::now();
    auto seconds = duration_cast<duration<double>>(end - start);
    printf("time(sec.): %lf\n", seconds);
    printf("collision:  %lu\n", set->count_collisions());
    printf("load:       %lf\n\n", set->load());
}