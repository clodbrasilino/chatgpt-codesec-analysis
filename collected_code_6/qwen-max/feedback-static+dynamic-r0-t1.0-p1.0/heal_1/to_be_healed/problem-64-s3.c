#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef int (*CompareFunc)(const void*, const void*);

int compareTuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    if (tupleA->first == tupleB->first)
        return tupleA->second - tupleB->second;
    else
        return tupleA->first - tupleB->first;
}

void sortTuples(Tuple *tuples, size_t count, CompareFunc cmp) {
    qsort(tuples, count, sizeof(Tuple), cmp);
}

int main() {
    Tuple tuples[] = {{3, 1}, {2, 2}, {3, 3}, {1, 4}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, count, compareTuples);

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }

    return 0;
}