#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int compare(const void *a, const void *b) {
    return ((Range *)a)->start - ((Range *)b)->start;
}

void findMissingRanges(Range *ranges, int n, int start, int end, Range **missing, int *missingCount) {
    *missingCount = 0;
    *missing = (Range *)malloc((end - start + 1) * sizeof(Range));
    if (*missing == NULL) {
        return;
    }

    int current = start;
    for (int i = 0; i < n; i++) {
        if (current < ranges[i].start) {
            (*missing)[*missingCount].start = current;
            (*missing)[*missingCount].end = ranges[i].start - 1;
            (*missingCount)++;
        }
        current = ranges[i].end + 1;
    }

    if (current <= end) {
        (*missing)[*missingCount].start = current;
        (*missing)[*missingCount].end = end;
        (*missingCount)++;
    }
}

int main() {
    Range ranges[] = {{3, 5}, {10, 12}, {15, 18}};
    int n = sizeof(ranges) / sizeof(ranges[0]);
    qsort(ranges, n, sizeof(Range), compare);

    int start = 1;
    int end = 20;
    Range *missing = NULL;
    int missingCount = 0;

    findMissingRanges(ranges, n, start, end, &missing, &missingCount);

    for (int i = 0; i < missingCount; i++) {
        printf("%d-%d\n", missing[i].start, missing[i].end);
    }

    free(missing);
    return 0;
}