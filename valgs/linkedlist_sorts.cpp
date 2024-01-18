#include "LinkedList.hpp"

template <typename T, class TList>
void bubble_sort(TList *list, size_t count, std::function<int(T, T)> compare)
{
    for (size_t i = 0; i < count; i++)
    {
        auto item = list->get_node_at(0);
        auto item_next = item->next;
        for (size_t k = 0; k < count - 1 - i; k++)
        {
            if (compare(item->data, item_next->data) > 0)
            {
                std::swap(item->data, item_next->data);
            }
            item = item_next;
            item_next = item_next->next;
        }
    }
}