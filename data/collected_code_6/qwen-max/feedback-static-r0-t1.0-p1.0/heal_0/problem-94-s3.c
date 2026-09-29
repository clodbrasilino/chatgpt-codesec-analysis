#include <stdio.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Record;

int findMinRecordIndex(Record *records, int size, int *outIndex) {
    if (size <= 0 || !records) return -1;

    int minVal = INT_MAX;
    *outIndex = -1;

    for (int i = 0; i < size; ++i) {
        if (records[i].value < minVal) {
            minVal = records[i].value;
            *outIndex = records[i].index;
        }
    }

    return 0;
}

int main() {
    Record records[] = {{0, 5}, {1, 3}, {2, 7}, {3, 1}, {4, 2}};
    int size = 5;
    int minIndex;

    if (findMinRecordIndex(records, size, &minIndex) == 0) {
        printf("Index of minimum value record: %d\n", minIndex);
    } else {
        printf("An error occurred.\n");
    }

    return 0;
}