#include <cstdio>
#include <iostream>
#include <optional>
#include "LinkedList.h"
#include <vector>

int main()
{
    std::vector<int>* vec = new std::vector<int>();
    vec->push_back(2);
    delete vec;
    LinkedList<int> *list = new LinkedList<int>();
    list->add_head(5);
    list->add_head(7);
    list->add_head(74);
    list->add_head(67);
    list->add_head(66336);
    list->set_at(1,5885);
    list->insert(5, 333);
    list->remove_at(3);

    /*while(list->count() != 0)
    {
        printf("%d\n", list->pop_tail().value());
    }*/

    for(auto iter = list->begin(); iter != list-> end(); ++iter)
    {
        std::cout << (*iter) << '\n';
    }

    for(auto& elem : (*list))
    {
         std::cout << elem << '\n';
    }
    //delete list;
    return 0;
}