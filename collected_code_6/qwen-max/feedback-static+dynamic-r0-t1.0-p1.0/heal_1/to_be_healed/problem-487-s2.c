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
    return (tupleA->second - tupleB->second);
}

void sort_tuples(Tuple *tuples, size_t length) {
    qsort(tuples, length, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{1, 3}, {4, 1}, {2, 2}};
    size_t length = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, length);

    for (size_t i = 0; i < length; ++i) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }

    return 0;
}