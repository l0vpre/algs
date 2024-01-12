#include <cstdio>
#include "LinkedList.h"
#include "HashSet.h"

int main()
{
    HashSet<int> *hash_set = new HashSet<int>();
    hash_set->add(30);
    hash_set->add(31);
    hash_set->add(32);
    hash_set->add(33);
    hash_set->add(34);
    hash_set->add(35);
    hash_set->remove(35);
    printf("%d\n\n", hash_set->count_collisions());
    int* arr = hash_set->to_array();
    for(int i = 0;i<6 ;i++)
    {
        printf("%d\n",arr[i]);
    }

    delete hash_set;

}