#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples_first(const void *a, const void *b) {
    int val_a = ((const Tuple *)a)->first;
    int val_b = ((const Tuple *)b)->first;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int compare_tuples_second(const void *a, const void *b) {
    int val_a = ((const Tuple *)a)->second;
    int val_b = ((const Tuple *)b)->second;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

typedef int (*CompareFunc)(const void *, const void *);

void sort_tuples(Tuple *array, size_t n, CompareFunc lambda) {
    if (array == NULL || n == 0 || lambda == NULL) {
        return;
    }
    qsort(array, n, sizeof(Tuple), lambda);
}

int main(void) {
    Tuple tuples[] = {{5, 2}, {2, 8}, {5, 1}, {1, 4}};
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, n, compare_tuples_first);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    sort_tuples(tuples, n, compare_tuples_second);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}