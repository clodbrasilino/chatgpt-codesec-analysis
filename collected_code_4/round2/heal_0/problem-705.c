#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int len;
    int *values;
} List;

int compareList(const void *a, const void *b) {
    List *listA = (List *) a;
    List *listB = (List *) b;

    if(listA->len != listB->len)
        return listA->len - listB->len;
    else {
        for(int i = 0; i<listA->len; ++i) {
            if(listA->values[i] != listB->values[i])
                return listA->values[i] - listB->values[i];
        }
    }

    return 0;
}

void sortLists(List* lists, size_t count) {
    qsort(lists, count, sizeof(List), compareList);
}

int main() {

    int values1[] = {1, 2, 3};
    int values2[] = {1, 2, 3, 4, 5};
    int values3[] = {1};
    int values4[] = {2};

    List lists[] = {
        { .len = sizeof(values1) / sizeof(int), .values = values1 }, 
        { .len = sizeof(values2) / sizeof(int), .values = values2 }, 
        { .len = sizeof(values3) / sizeof(int), .values = values3 }, 
        { .len = sizeof(values4) / sizeof(int), .values = values4 }
    }; 

    size_t listCount = sizeof(lists) / sizeof(List);

    sortLists(lists, listCount);

    for(size_t i = 0; i < listCount; ++i) {
        printf("list %zu: length %d\n", i, lists[i].len);
        for (size_t j = 0; j < lists[i].len; ++j) {
            printf("%d, ", lists[i].values[j]);
        }
        printf("\n");
    }

    return 0;
}