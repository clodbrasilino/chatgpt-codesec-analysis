#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    return (tupleA->second - tupleB->second);
}

void sort_tuples_by_second(Tuple *tuples, size_t n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{1, 3}, {2, 1}, {3, 2}};
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples_by_second(tuples, n);

    for (size_t i = 0; i < n; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}