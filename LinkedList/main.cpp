#include <cstdio>
#include <iostream>
#include <optional>
#include <LinkedList.h>

int main()
{
    LinkedList<int> *list = new LinkedList<int>();
    list->add(5);
    list->add(7);
    list->add(74);
    list->add(67);
    list->add(6666);
    list->set_at(1,5885);
    for(int i = 0; i < list->count(); i++)
    {
        printf("%d\n",list->get_at(i).value());
    }
    return 0;
}