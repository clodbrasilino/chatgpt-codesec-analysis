#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

int cmpfunc(const void * a, const void * b) {
    /* Possible weaknesses found:
     *  Variable 'ta' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *ta = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tb' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tb = (Tuple *)b;
    if (ta->value > tb->value) return 1;
    if (ta->value < tb->value) return -1;
    return 0;
}

void sortTuple(Tuple *tuples, int n) {
    qsort(tuples, n, sizeof(Tuple), cmpfunc);
}

int main() {
    Tuple tuples[] = {{1, 3.5f}, {2, 1.2f}, {3, 4.8f}, {4, 0.9f}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    sortTuple(tuples, n);

    for (int i = 0; i < n; ++i) {
        printf("%d: %.1f\n", tuples[i].id, tuples[i].value);
    }

    return 0;
}