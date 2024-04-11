#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int integer;
    float floating;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;
    return (tupleA->floating > tupleB->floating) - (tupleA->floating < tupleB->floating);
}

void sortTuple(Tuple arr[], int n) {
    qsort(arr, n, sizeof(Tuple), compare);
}

int main() {
    Tuple arr[] = {{1, 2.2}, {2, 1.1}, {3, 3.3}};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortTuple(arr, n);

    for (int i = 0; i < n; i++) {
        printf("Integer: %d, Float: %.2f\n", arr[i].integer, arr[i].floating);
    }

    return 0;
}