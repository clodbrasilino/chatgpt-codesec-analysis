#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    return tuple_a->second - tuple_b->second;
}

void sort_tuples(Tuple *tuples, int n) {
    if (tuples == NULL || n <= 0) {
        return;
    }
    qsort(tuples, n, sizeof(Tuple), compare_tuples);
}

int main(void) {
    Tuple tuples[] = {
        {1, 3},
        {2, 1},
        {3, 2},
        {4, 5},
        {5, 4}
    };
    int n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}