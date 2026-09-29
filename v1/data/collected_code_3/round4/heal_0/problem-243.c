#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} tuple;

int compare(const void *a, const void *b) {
    tuple *tupleA = (tuple *)a;
    tuple *tupleB = (tuple *)b;
    return tupleA->first - tupleB->first;
}

void sortTuples(tuple *arr, int n) {
    qsort(arr, n, sizeof(tuple), compare);
}

int main() {
    tuple arr[] = {{5, 2}, {1, 3}, {4, 1}, {2, 2}, {3, 1}};
    int n = sizeof(arr) / sizeof(arr[0]);

    sortTuples(arr, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d) ", arr[i].first, arr[i].second);
    }

    return 0;
}