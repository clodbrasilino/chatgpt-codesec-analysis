#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first < tb->first) return -1;
    if (ta->first > tb->first) return 1;
    return 0;
}

void sort_tuples(Tuple *arr, size_t n) {
    if (arr == NULL || n == 0) return;
    qsort(arr, n, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple list[] = {{3, 30}, {1, 10}, {2, 20}, {1, 15}, {3, 25}};
    size_t n = sizeof(list) / sizeof(list[0]);
    size_t i;

    printf("Original list:\n");
    for (i = 0; i < n; i++) {
        printf("(%d, %d) ", list[i].first, list[i].second);
    }
    printf("\n");

    sort_tuples(list, n);

    printf("Sorted list:\n");
    for (i = 0; i < n; i++) {
        printf("(%d, %d) ", list[i].first, list[i].second);
    }
    printf("\n");

    return 0;
}