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
    return tupleA->first - tupleB->first;
}

void sort_tuples(Tuple *tuples, int n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{3, 2}, {1, 5}, {3, 8}, {2, 7}, {1, 9}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}