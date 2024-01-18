#include <cstddef>
#include <functional>
#include <utility>

template <typename T>
void bubble_sort(T *array, size_t count, std::function<int(T, T)> compare)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t k = 0; k < count - 1-i; k++)
        {
            if (compare(array[k],array[k + 1])>0)
            {
                std::swap(array[k],array[k + 1]);
            }
        }
    }
}

