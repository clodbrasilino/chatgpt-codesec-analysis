#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

int getMissingRanges(int* nums, int numsSize, int start, int end, Range** outRanges) {
    if (outRanges == NULL) return -1;
    *outRanges = NULL;
    if (start > end) return 0;
    if (numsSize < 0) return -1;
    if (nums == NULL && numsSize > 0) return -1;

    int count = 0;
    long long cur = (long long)start;
    int i = 0;

    while (i < numsSize && nums[i] < start) i++;

    while (i < numsSize) {
        if (nums[i] > end) break;
        long long num = (long long)nums[i];
        if (num > cur) {
            count++;
        }
        if (num >= cur) {
            cur = num + 1;
        }
        i++;
    }
    if (cur <= (long long)end) {
        count++;
    }

    if (count == 0) {
        return 0;
    }

    Range* ranges = (Range*)malloc(count * sizeof(Range));
    if (ranges == NULL) {
        return -1;
    }
    *outRanges = ranges;

    int outIdx = 0;
    cur = (long long)start;
    i = 0;
    while (i < numsSize && nums[i] < start) i++;

    while (i < numsSize) {
        if (nums[i] > end) break;
        long long num = (long long)nums[i];
        if (num > cur) {
            ranges[outIdx].start = (int)cur;
            ranges[outIdx].end = (int)(num - 1);
            outIdx++;
        }
        if (num >= cur) {
            cur = num + 1;
        }
        i++;
    }
    if (cur <= (long long)end) {
        ranges[outIdx].start = (int)cur;
        ranges[outIdx].end = (int)end;
        outIdx++;
    }

    return outIdx;
}

int main() {
    int nums[] = {0, 1, 3, 50, 75};
    int start = 0, end = 99;
    Range* ranges = NULL;
    int count = getMissingRanges(nums, sizeof(nums)/sizeof(nums[0]), start, end, &ranges);
    if (count < 0) {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("[%d, %d] ", ranges[i].start, ranges[i].end);
    }
    printf("\n");
    free(ranges);
    return 0;
}