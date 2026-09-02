#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->first - ((Tuple *)b)->first;
}

void extractSinglyOccurringElements(Tuple *tuples, int n, int *result, int *resultSize) {
    qsort(tuples, n, sizeof(Tuple), compare);
    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (tuples[i].first == tuples[i-1].first) {
            count++;
        } else {
            if (count == 1) {
                result[(*resultSize)++] = tuples[i-1].first;
            }
            count = 1;
        }
    }
    if (count == 1) {
        result[(*resultSize)++] = tuples[n-1].first;
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 5}, {6, 7}, {8, 9}, {3, 10}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result[100];
    int resultSize = 0;

    extractSinglyOccurringElements(tuples, n, result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}