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
    for (int i = 0; i < n; ) {
        int count = 1;
        while (i + count < n && tuples[i].first == tuples[i + count].first) {
            count++;
        }
        if (count == 1) {
            result[(*resultSize)++] = tuples[i].second;
        }
        i += count;
    }
}

int main() {
    Tuple tuples[] = {{1, 10}, {2, 20}, {1, 30}, {3, 40}, {4, 50}, {4, 60}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result[100];
    int resultSize = 0;

    extractSinglyOccurringElements(tuples, n, result, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    return 0;
}