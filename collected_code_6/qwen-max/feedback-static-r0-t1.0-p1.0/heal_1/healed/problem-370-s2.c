#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare(const void *a, const void *b) {
    const Tuple *tupleA = a;
    const Tuple *tupleB = b;
    if (tupleA->value < tupleB->value) return -1;
    if (tupleA->value > tupleB->value) return 1;
    return 0;
}

void sort_tuples_by_float(Tuple *tuples, size_t count) {
    qsort(tuples, count, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{1, 3.5f}, {2, 1.2f}, {3, 4.8f}, {4, 2.1f}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    sort_tuples_by_float(tuples, count);
    for (size_t i = 0; i < count; ++i) {
        printf("%d: %f\n", tuples[i].id, tuples[i].value);
    }
    return 0;
}