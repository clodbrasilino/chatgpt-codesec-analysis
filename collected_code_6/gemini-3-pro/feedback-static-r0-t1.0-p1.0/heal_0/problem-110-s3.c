#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

void find_missing_ranges(int* nums, int numsSize, int lower, int upper, Range** result, int* returnSize) {
    if (result == NULL || returnSize == NULL) {
        return;
    }

    *result = (Range*)malloc((numsSize + 1) * sizeof(Range));
    if (*result == NULL) {
        *returnSize = 0;
        return;
    }

    *returnSize = 0;
    long long next = (long long)lower;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < next) {
            continue;
        }

        if (nums[i] == next) {
            next++;
            continue;
        }

        if (nums[i] > upper) {
            break;
        }

        (*result)[*returnSize].start = (int)next;
        (*result)[*returnSize].end = nums[i] - 1;
        (*returnSize)++;
        
        next = (long long)nums[i] + 1;
    }

    if (next <= upper) {
        (*result)[*returnSize].start = (int)next;
        (*result)[*returnSize].end = upper;
        (*returnSize)++;
    }
}

int main() {
    int nums[] = {0, 1, 3, 50, 75};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int lower = 0;
    int upper = 99;

    Range* missingRanges = NULL;
    int returnSize = 0;

    find_missing_ranges(nums, numsSize, lower, upper, &missingRanges, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        if (missingRanges[i].start == missingRanges[i].end) {
            printf("[%d]\n", missingRanges[i].start);
        } else {
            printf("[%d, %d]\n", missingRanges[i].start, missingRanges[i].end);
        }
    }

    free(missingRanges);
    missingRanges = NULL;

    return 0;
}