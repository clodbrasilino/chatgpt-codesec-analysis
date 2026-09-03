#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int compare(const void *a, const void *b) {
    return ((Range *)a)->start - ((Range *)b)->start;
}

void findMissingRanges(Range *ranges, int rangeCount, int start, int end, Range **missingRanges, int *missingCount) {
    int current = start;
    for (int i = 0; i < rangeCount; i++) {
        if (current < ranges[i].start) {
            (*missingRanges)[*missingCount].start = current;
            (*missingRanges)[*missingCount].end = ranges[i].start - 1;
            (*missingCount)++;
        }
        current = ranges[i].end + 1;
    }
    if (current <= end) {
        (*missingRanges)[*missingCount].start = current;
        (*missingRanges)[*missingCount].end = end;
        (*missingCount)++;
    }
}

int main() {
    Range ranges[] = {{5, 8}, {10, 12}, {20, 25}};
    int rangeCount = sizeof(ranges) / sizeof(ranges[0]);
    int start = 1;
    int end = 30;

    qsort(ranges, rangeCount, sizeof(Range), compare);

    Range *missingRanges = (Range *)malloc((end - start + 1) * sizeof(Range));
    int missingCount = 0;

    findMissingRanges(ranges, rangeCount, start, end, &missingRanges, &missingCount);

    for (int i = 0; i < missingCount; i++) {
        printf("%d-%d\n", missingRanges[i].start, missingRanges[i].end);
    }

    free(missingRanges);
    return 0;
}