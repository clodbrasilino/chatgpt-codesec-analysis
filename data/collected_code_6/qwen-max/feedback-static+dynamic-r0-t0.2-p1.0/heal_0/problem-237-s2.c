#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Record;

int compare(const void *a, const void *b) {
    return ((Record *)a)->value - ((Record *)b)->value;
}

int countSimilarOccurrences(Record *records, int n) {
    if (n <= 1) return 0;

    qsort(records, n, sizeof(Record), compare);

    int count = 1;
    int maxCount = 0;
    for (int i = 1; i < n; ++i) {
        if (records[i].value == records[i - 1].value) {
            count++;
        } else {
            if (count > 1) {
                maxCount += count;
            }
            count = 1;
        }
    }
    if (count > 1) {
        maxCount += count;
    }

    return maxCount;
}

int main() {
    Record records[] = {{1, 2}, {2, 3}, {3, 2}, {4, 3}, {5, 2}};
    int n = sizeof(records) / sizeof(records[0]);
    int result = countSimilarOccurrences(records, n);
    printf("Number of similar occurrences: %d\n", result);
    return 0;
}