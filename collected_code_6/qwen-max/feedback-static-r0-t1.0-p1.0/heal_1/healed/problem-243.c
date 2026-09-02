#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    return tupleA->first - tupleB->first;
}

void sort_tuples(Tuple *tuples, size_t len) {
    qsort(tuples, len, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{3, 4}, {1, 2}, {3, 5}, {1, 6}, {2, 7}};
    size_t len = sizeof(tuples) / sizeof(tuples[0]);
    sort_tuples(tuples, len);
    for (size_t i = 0; i < len; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    return 0;
}