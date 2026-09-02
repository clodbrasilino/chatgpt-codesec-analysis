#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Record;

int compare(const void *a, const void *b) {
    return ((Record *)a)->value - ((Record *)b)->value;
}

int countSimilarOccurrences(Record *records, int size) {
    if (size <= 1) return 0;

    qsort(records, size, sizeof(Record), compare);

    int count = 1;
    int similarCount = 0;

    for (int i = 1; i < size; i++) {
        if (records[i].value == records[i - 1].value) {
            count++;
        } else {
            if (count > 1) {
                similarCount += count;
            }
            count = 1;
        }
    }

    if (count > 1) {
        similarCount += count;
    }

    return similarCount;
}

int main() {
    Record records[] = {{1, 10}, {2, 20}, {3, 10}, {4, 30}, {5, 10}};
    int size = sizeof(records) / sizeof(records[0]);

    int result = countSimilarOccurrences(records, size);
    printf("Number of similar occurrences: %d\n", result);

    return 0;
}