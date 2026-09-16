#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    if (tuple_a->first < tuple_b->first) return -1;
    if (tuple_a->first > tuple_b->first) return 1;
    return 0;
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {{5, 2}, {2, 8}, {5, 1}, {1, 4}, {2, 9}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}