#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

int compare(const void* a, const void* b) {
    Tuple* tupleA = (Tuple*)a;
    Tuple* tupleB = (Tuple*)b;
    return tupleA->value - tupleB->value;
}

void find_min_k(Tuple* tuples, int size, int k) {
    qsort(tuples, size, sizeof(Tuple), compare);
    for(int i = 0; i < k; i++) {
        printf("ID: %d, Value: %d\n", tuples[i].id, tuples[i].value);
    }
}

int main() {
    Tuple tuples[] = {{1, 20}, {2, 15}, {3, 30}, {4, 10}, {5, 25}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;
    find_min_k(tuples, size, k);
    return 0;
}