#include <ostream>
#define VALGS_TESTING

#include "../valgs/HashDictionary.hpp"
#include "../valgs/HashSet.hpp"
#include "../valgs/Sorts.cpp"
#include "../valgs/hashes.h"
#include <chrono>
// #include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#define len(x) sizeof(x) / sizeof(x[0])
int compare(int a, int b)
{
    return a - b;
}
// TODO: ???
int main1()
{
    auto hash_set = std::make_unique<HashSet<std::string>>();
    auto hash_dict = std::make_unique<HashDictionary<std::string, size_t, Hash>>();
    std::ifstream fin("tests/words.txt");
    std::string temp;
    size_t num = 0;
    size_t max_count = 5'000'000;
    size_t count = 0;
    while (count < max_count && fin >> temp)
    {
        hash_dict->insert(temp, num);
        hash_set->add(temp);
        num += 5;
        count++;
    }
    // printf("%lu\n", hash_dict->get("accept").value());

    std::cout << "Hash set:\n"
              << "Count of elements: " << hash_set->count() << '\n'
              << "Count of buckets: " << hash_set->buckets_count() << '\n'
              << std::endl;

    std::cout << "Hash dictionary:\n"
              << "Count of elements: " << hash_dict->count() << '\n'
              << "Count of buckets: " << hash_dict->buckets_count() << '\n'
              << std::endl;
    return 0;
}

int main()
{

    int arr[] = {3, 5, 42, 463, 78, 22, 265, -3, -294};
    size_t count = len(arr);
    bubble_sort<int>(arr, count, compare);
    std::cout << "count:"<<count<<std::endl;
    for (size_t i = 0; i < count; i++)
    {
        std::cout << arr[i] << " " ;
    }
    std::cout<<std::endl;
    return 0;
}

// TODO: benchmark.cpp
// TODO: replace STL vector with array
// TODO: allocate set inside the function instead of accepting as a parameter
template <typename T, typename THash>
void benchmark_set(std::vector<T> *vec, HashSet<T, THash> *set)
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
