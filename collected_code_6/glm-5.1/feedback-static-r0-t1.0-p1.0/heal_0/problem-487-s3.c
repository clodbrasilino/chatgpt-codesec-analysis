#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int last;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->last < tb->last) return -1;
    if (ta->last > tb->last) return 1;
    return 0;
}

void sort_tuples(Tuple *tuples, size_t n) {
    if (tuples == NULL || n == 0) {
        return;
    }
    qsort(tuples, n, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {{1, 5}, {2, 2}, {3, 8}, {4, 1}};
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, n);

    for (size_t i = 0; i < n; i++) {
        printf("{%d, %d}\n", tuples[i].first, tuples[i].last);
    }

    return 0;
}