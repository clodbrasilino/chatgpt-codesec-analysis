#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->first - ((Tuple *)b)->first;
}

void extractSinglyOccurring(Tuple *tuples, int n, Tuple *result, int *resultSize) {
    qsort(tuples, n, sizeof(Tuple), compare);
    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (tuples[i].first == tuples[i-1].first) {
            count++;
        } else {
            if (count == 1) {
                result[*resultSize] = tuples[i-1];
                (*resultSize)++;
            }
            count = 1;
        }
    }
    if (count == 1) {
        result[*resultSize] = tuples[n-1];
        (*resultSize)++;
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {1, 5}, {6, 7}, {8, 9}, {3, 10}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    Tuple result[n];
    int resultSize = 0;

    extractSinglyOccurring(tuples, n, result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    return 0;
}