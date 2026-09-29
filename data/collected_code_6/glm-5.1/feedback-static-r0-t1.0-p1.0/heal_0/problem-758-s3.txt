#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

typedef struct {
    int *data;
    size_t size;
} IntList;

int compare_int_lists(const void *a, const void *b) {
    const IntList *la = (const IntList *)a;
    const IntList *lb = (const IntList *)b;
    
    if (la->size != lb->size) {
        return (la->size > lb->size) - (la->size < lb->size);
    }
    
    for (size_t i = 0; i < la->size; i++) {
        if (la->data[i] != lb->data[i]) {
            return (la->data[i] > lb->data[i]) - (la->data[i] < lb->data[i]);
        }
    }
    
    return 0;
}

size_t count_unique_lists(IntList *lists, size_t count) {
    if (count == 0) {
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (lists[i].data != NULL && lists[i].size > 0) {
            qsort(lists[i].data, lists[i].size, sizeof(int), compare_ints);
        }
    }

    qsort(lists, count, sizeof(IntList), compare_int_lists);

    size_t unique_count = 1;
    for (size_t i = 1; i < count; i++) {
        if (compare_int_lists(&lists[i - 1], &lists[i]) != 0) {
            unique_count++;
        }
    }

    return unique_count;
}

int main(void) {
    int a1[] = {3, 1, 2};
    int a2[] = {1, 2, 3};
    int a3[] = {4, 5};
    int a4[] = {5, 4, 6};
    int a5[] = {7};
    int a6[] = {7};

    IntList lists[] = {
        {a1, sizeof(a1) / sizeof(a1[0])},
        {a2, sizeof(a2) / sizeof(a2[0])},
        {a3, sizeof(a3) / sizeof(a3[0])},
        {a4, sizeof(a4) / sizeof(a4[0])},
        {a5, sizeof(a5) / sizeof(a5[0])},
        {a6, sizeof(a6) / sizeof(a6[0])}
    };

    size_t total_lists = sizeof(lists) / sizeof(lists[0]);
    size_t unique = count_unique_lists(lists, total_lists);

    printf("%zu\n", unique);

    return 0;
}