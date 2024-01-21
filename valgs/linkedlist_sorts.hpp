#ifndef LINKED_LIST_SORTS_HPP
#define LINKED_LIST_SORTS_HPP

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

template <typename T, class TList>
void quick_sort(TList *list, size_t count, std::function<int(T, T)> compare)
{
    if (count <= 1)
    {
        return;
    }
    auto pivot = list->pop_tail().value();
    TList list_less;
    TList list_more;

    while (list->count() != 0)
    {
        auto elem = list->pop_tail().value();
        if (compare(elem, pivot) < 0)
        {
            list_less.add_head(elem);
        }
        else
        {
            list_more.add_head(elem);
        }
    }
    quick_sort(&list_less, list_less.count(), compare);
    quick_sort(&list_more, list_more.count(), compare);
    for (auto &item : list_less)
    {
        list->add_head(item);
    }
    list->add_head(pivot);
    for (auto &item : list_more)
    {
        list->add_head(item);
    }
}

template <typename T, class TList>
void merge_sort(TList *list, size_t count, std::function<int(T, T)> compare)
{
    if (count <= 1)
    {
        return;
    }

    TList l_list;
    TList r_list;

    for (size_t _ = 0; _ < count / 2; _++)
    {
        l_list.add_head(list->pop_tail().value());
    }
    for (size_t _ = 0; list->count() > 0; _++)
    {
        r_list.add_head(list->pop_tail().value());
    }
    merge_sort(&l_list, l_list.count(), compare);
    merge_sort(&r_list, r_list.count(), compare);

    while (l_list.count() > 0)
    {
        if (r_list.count() > 0 && compare(l_list.tail().value(), r_list.tail().value()) > 0)
        {
            list->add_head(r_list.pop_tail().value());
        }
        else
        {
            list->add_head(l_list.pop_tail().value());
        }
    }
    while (r_list.count() > 0)
    {
        list->add_head(r_list.pop_tail().value());
    }
}

#endif // LINKED_LIST_SORTS_HPP
