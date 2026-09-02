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

void sortTuples(Tuple *tuples, size_t count, int (*cmp)(const void *, const void *)) {
    qsort(tuples, count, sizeof(Tuple), cmp);
}

int main() {
    Tuple tuples[] = {{3, 4}, {1, 2}, {5, 6}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, count, compare);

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}