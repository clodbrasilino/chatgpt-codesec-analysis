#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    return (tupleA->first - tupleB->first);
}

void sortTuples(Tuple *tuples, size_t n, int (*comp)(const void *, const void *)) {
    qsort(tuples, n, sizeof(Tuple), comp);
}

int main() {
    Tuple tuples[] = {{3, 2}, {1, 4}, {5, 0}};
    size_t n = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, n, compare);

    for (size_t i = 0; i < n; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}