#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *list1;
    int *list2;
    int *list3;
    size_t size;
} ListSet;

size_t countCommonPairs(ListSet *ls) {
    size_t count = 0;
    for (size_t i = 0; i < ls->size; ++i) {
        if (ls->list1[i] == ls->list2[i] && ls->list2[i] == ls->list3[i]) {
            ++count;
        }
    }
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {1, 2, 5, 6};
    int list3[] = {1, 2, 7, 8};

    size_t size = sizeof(list1) / sizeof(list1[0]);

    ListSet ls = {list1, list2, list3, size};

    size_t commonPairs = countCommonPairs(&ls);

    printf("Number of common pairs: %zu\n", commonPairs);

    return 0;
}