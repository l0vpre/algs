#ifndef TEST_SORTS_HPP
#define TEST_SORTS_HPP

#include "../valgs/array_sorts.hpp"
#include "../valgs/linkedlist_sorts.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct BenchArraySortParams
{
    using cmp_t = std::function<int(T, T)>;

    std::vector<T> vec;
    const char *name;
    std::function<void(T *, size_t, cmp_t)> sort;
    cmp_t compare;
};

template <typename T, class TList>
struct BenchLinkedListSortParams
{
    using cmp_t = std::function<int(T, T)>;

    TList list;
    const char *name;
    std::function<void(TList *, size_t, cmp_t)> sort;
    cmp_t compare;
};

template <class TList>
TList copy_linked_list(TList *list);

template <typename T>
void bench_array_sort(const BenchArraySortParams<T> &params);

template <class TList>
inline void bench_all_linked_list_sorts(TList *list, bool bench_slow_sorts = false);

inline void bench_all_array_sorts(std::vector<std::string> vec, bool bench_slow_sorts = false);

template <class TList>
TList copy_linked_list(TList *list)
{
    TList copy;
    for (auto &item : *list)
    {
        copy.add_head(item);
    }
    return copy;
}

inline void bench_all_array_sorts(std::vector<std::string> vec, bool bench_slow_sorts)
{
    auto qs_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Quick sort",
        .sort = quick_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(qs_params);

    auto ms_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Merge sort",
        .sort = merge_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(ms_params);

    auto hs_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Heap sort",
        .sort = heap_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(hs_params);

    if (!bench_slow_sorts)
    {
        return;
    }

    auto bs_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Bubble sort",
        .sort = bubble_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(bs_params);

    auto ss_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Selection sort",
        .sort = selection_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(ss_params);

    auto is_params = BenchArraySortParams<std::string>{
        .vec = vec,
        .name = "Insertion sort",
        .sort = insetion_sort<std::string>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_array_sort<std::string>(is_params);
}

template <typename T>
void bench_array_sort(const BenchArraySortParams<T> &params)
{
    using namespace std::chrono;

    auto vec = params.vec;
    auto name = params.name;
    auto sort = params.sort;
    auto compare = params.compare;

    auto start = high_resolution_clock::now();
    std::cout << name << " for vector" << std::endl;
    sort(vec.data(), vec.size(), compare);
    auto end = high_resolution_clock::now();
    auto seconds = duration_cast<duration<double>>(end - start).count();
    std::cout << "time(sec.) " << seconds << "\n" << std::endl;
}

template <class TList>
inline void bench_all_linked_list_sorts(TList *list, bool bench_slow_sorts)
{
    auto qs_params = BenchLinkedListSortParams<std::string, TList>{
        .list = copy_linked_list(list),
        .name = "Quick sort",
        .sort = quick_sort<std::string, TList>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_linked_list_sort<std::string, TList>(qs_params);

    auto ms_params = BenchLinkedListSortParams<std::string, TList>{
        .list = copy_linked_list(list),
        .name = "Merge sort",
        .sort = merge_sort<std::string, TList>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_linked_list_sort<std::string, TList>(ms_params);

    if (!bench_slow_sorts)
    {
        return;
    }

    auto bs_params = BenchLinkedListSortParams<std::string, TList>{
        .list = copy_linked_list(list),
        .name = "Bubble sort",
        .sort = bubble_sort<std::string, TList>,
        .compare = [](std::string a, std::string b) { return a.compare(b); },
    };

    bench_linked_list_sort<std::string, TList>(bs_params);
}

template <typename T, class TList>
void bench_linked_list_sort(BenchLinkedListSortParams<T, TList> params)
{
    using namespace std::chrono;

    auto list = &params.list;
    auto name = params.name;
    auto sort = params.sort;
    auto compare = params.compare;

    auto start = high_resolution_clock::now();
    std::cout << name << " for linked list" << std::endl;
    sort(list, list->count(), compare);
    auto end = high_resolution_clock::now();
    auto seconds = duration_cast<duration<double>>(end - start).count();
    std::cout << "time(sec.) " << seconds << "\n" << std::endl;
}

#endif // TEST_SORTS_HPP