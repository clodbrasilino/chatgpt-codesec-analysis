#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Range;

void sortRanges(Range *ranges, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (ranges[j].start > ranges[j + 1].start) {
                Range temp = ranges[j];
                ranges[j] = ranges[j + 1];
                ranges[j + 1] = temp;
            }
        }
    }
}

void findMissingRanges(int *list, int listSize, int rangeStart, int rangeEnd, Range **result, int *resultSize) {
    *result = (Range *)malloc((rangeEnd - rangeStart + 1) * sizeof(Range));
    *resultSize = 0;

    int current = rangeStart;

    for (int i = 0; i < listSize; ++i) {
        while (current < list[i]) {
            (*result)[*resultSize].start = current;
            (*result)[*resultSize].end = (list[i] - 1 < rangeEnd) ? list[i] - 1 : rangeEnd;
            (*resultSize)++;
            current = (list[i] < rangeEnd) ? list[i] : rangeEnd + 1;
        }
        current = (list[i] + 1 <= rangeEnd) ? list[i] + 1 : rangeEnd + 1;
    }

    if (current <= rangeEnd) {
        (*result)[*resultSize].start = current;
        (*result)[*resultSize].end = rangeEnd;
        (*resultSize)++;
    }
}

int main() {
    int list[] = {2, 4, 7, 10};
    int listSize = 4;
    int rangeStart = 1;
    int rangeEnd = 12;

    Range *result;
    int resultSize;

    findMissingRanges(list, listSize, rangeStart, rangeEnd, &result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("(%d, %d)\n", result[i].start, result[i].end);
    }

    free(result);
    return 0;
}