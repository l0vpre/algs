#include <cstddef>
#include <functional>
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
