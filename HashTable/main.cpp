#include <cstdio>
#include "LinkedList.h"
#include "HashSet.h"
#include <fstream>
#include <vector>
#include <chrono>

template <typename T, typename THash>
void test_set(std::vector<T> *vec, HashSet<T, THash> *set);

int main()
{
    struct Hash
    {
    public:
        size_t operator()(const std::string& s)
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
        size_t operator()(const std::string& s)
        {
            size_t hash = 5381;
            for (char c : s)
            {
                hash = ((hash << 5) + hash) + c;
            }

            return hash;
        }
    };

    HashSet<std::string, std::hash<std::string>> *hash_set = new HashSet<std::string, std::hash<std::string>>();
    HashSet<std::string, Hash> *myhash_set = new HashSet<std::string, Hash>();
    HashSet<std::string, Djb2Hash> *djb2hash_set = new HashSet<std::string, Djb2Hash>();

    std::string temp;
    std::ifstream fin("words.txt");
    auto vec = new std::vector<std::string>();

    while (fin >> temp)
    {
        vec->emplace_back(temp);
    }
    printf("testing my hash set\n");
    test_set(vec, myhash_set);
    printf("testing std hash set\n");
    test_set(vec, hash_set);
    printf("testing djb2hash set\n");
    test_set(vec, djb2hash_set);

    delete hash_set;
    delete myhash_set;
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
    auto end =  high_resolution_clock::now();
    auto seconds = duration_cast<duration<double>>(end - start);
    printf("time(sec.): %lf\n", seconds);
    printf("collision:  %lu\n", set->count_collisions());
    printf("load:       %lf\n\n", set->load());
}