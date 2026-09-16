#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int compare_by_second(const void *a, const void *b) {
    Pair *pair_a = (Pair *)a;
    Pair *pair_b = (Pair *)b;
    if (pair_a->second < pair_b->second) return -1;
    if (pair_a->second > pair_b->second) return 1;
    return 0;
}

void sort_by_second(Pair *list, int size) {
    qsort(list, size, sizeof(Pair), compare_by_second);
}

int main(void) {
    Pair list[] = {
        {1, 5},
        {2, 3},
        {3, 8},
        {4, 1},
        {5, 6}
    };
    int size = sizeof(list) / sizeof(list[0]);
    int i;

    sort_by_second(list, size);

    for (i = 0; i < size; i++) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }

    return 0;
}