#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int compare(const void *a, const void *b) {
    return ((Range *)a)->start - ((Range *)b)->start;
}

void findMissingRanges(Range *ranges, int n, int start, int end, Range *missing, int *missingCount) {
    qsort(ranges, n, sizeof(Range), compare);
    int current = start;

    for (int i = 0; i < n; i++) {
        if (current < ranges[i].start) {
            missing[*missingCount].start = current;
            missing[*missingCount].end = ranges[i].start - 1;
            (*missingCount)++;
        }
        if (ranges[i].end >= current) {
            current = ranges[i].end + 1;
        }
    }

    if (current <= end) {
        missing[*missingCount].start = current;
        missing[*missingCount].end = end;
        (*missingCount)++;
    }
}

int main() {
    Range ranges[] = {
        {5, 10},
        {20, 30},
        {60, 80}
    };
    int n = 3;
    int start = 1;
    int end = 85;
    Range missing[100];
    int missingCount = 0;

    findMissingRanges(ranges, n, start, end, missing, &missingCount);

    for (int i = 0; i < missingCount; i++) {
        printf("Missing range: %d to %d\n", missing[i].start, missing[i].end);
    }

    return 0;
}