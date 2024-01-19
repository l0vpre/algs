#include <cstddef>
#include <functional>
#include <memory>
#include <utility>

template <typename T>
void bubble_sort(T *array, size_t count, std::function<int(T, T)> compare)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t k = 0; k < count - 1 - i; k++)
        {
            if (compare(array[k], array[k + 1]) > 0)
            {
                std::swap(array[k], array[k + 1]);
            }
        }
    }
}

template <typename T>
void selection_sort(T *array, size_t count, std::function<int(T, T)> compare)
{

    for (size_t i = 0; i < count; i++)
    {
        size_t index_min = i;
        for (size_t k = i; k < count; k++)
        {
            if (compare(array[k], array[index_min]) < 0)
            {
                index_min = k;
            }
        }

        std::swap(array[i], array[index_min]);
    }
}

template <typename T>
void insetion_sort(T *array, size_t count, std::function<int(T, T)> compare)
{
    for (size_t i = 1; i < count; i++)
    {
        size_t j = i;
        while (j > 0 && compare(array[j], array[j - 1]) < 0)
        {
            std::swap(array[j], array[j - 1]);
            j--;
        }
    }
}

template <typename T>
void quick_sort(T *array, size_t count, std::function<int(T, T)> compare)
{
    if (count <= 1)
    {
        return;
    }

    T pivot = array[count / 2];
    size_t pivot_index = 0;
    size_t current_index = 1;
    std::swap(array[count / 2], array[0]);
    while (current_index < count)
    {
        if (compare(array[current_index], pivot) < 0)
        {
            pivot_index++;
            std::swap(array[current_index], array[pivot_index]);
        }
        current_index++;
    }
    std::swap(array[0], array[pivot_index]);
    quick_sort(array, pivot_index, compare);
    quick_sort(array + pivot_index + 1, count - (pivot_index + 1), compare);
}

template <typename T>
void merge_sort(T *array, size_t count, std::function<int(T, T)> compare)
{
    if (count <= 1)
    {
        return;
    }
    size_t l_count = count / 2;
    size_t r_count = count - l_count;
    auto l_arr = new T[l_count];
    auto r_arr = new T[r_count];

    for (size_t l_idx = 0; l_idx < l_count; l_idx++)
    {
        l_arr[l_idx] = array[l_idx];
    }
    for (size_t arr_idx = l_count, r_idx = 0; r_idx < r_count; arr_idx++, r_idx++)
    {
        r_arr[r_idx] = array[arr_idx];
    }
    merge_sort(l_arr, l_count, compare);
    merge_sort(r_arr, r_count, compare);

    size_t r_idx = 0;
    size_t l_idx = 0;
    size_t arr_idx = 0;

    while (l_idx < l_count)
    {
        if (r_idx < r_count && compare(l_arr[l_idx], r_arr[r_idx]) > 0)
        {
            array[arr_idx] = r_arr[r_idx];
            r_idx++;
        }
        else
        {
            array[arr_idx] = l_arr[l_idx];
            l_idx++;
        }
        arr_idx++;
    }
    while (r_idx < r_count)
    {
        array[arr_idx] = r_arr[r_idx];
        r_idx++;
        arr_idx++;
    }

    delete[] l_arr;
    delete[] r_arr;
}
