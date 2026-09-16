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

    int capacity = 10;
    *result = (Range*)malloc(capacity * sizeof(Range));
    if (*result == NULL) {
        *returnSize = 0;
        return;
    }

    *returnSize = 0;
    long long next = lower;

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] < next) {
            continue;
        }
        
        if (nums[i] == next) {
            next++;
            continue;
        }

        if (*returnSize >= capacity) {
            capacity *= 2;
            Range* temp = (Range*)realloc(*result, capacity * sizeof(Range));
            if (temp == NULL) {
                free(*result);
                *result = NULL;
                *returnSize = 0;
                return;
            }
            *result = temp;
        }
        (*result)[*returnSize].start = (int)next;
        (*result)[*returnSize].end = nums[i] - 1;
        (*returnSize)++;
        next = (long long)nums[i] + 1;
    }

    if (next <= upper) {
        if (*returnSize >= capacity) {
            capacity += 1;
            Range* temp = (Range*)realloc(*result, capacity * sizeof(Range));
            if (temp == NULL) {
                free(*result);
                *result = NULL;
                *returnSize = 0;
                return;
            }
            *result = temp;
        }
        (*result)[*returnSize].start = (int)next;
        (*result)[*returnSize].end = upper;
        (*returnSize)++;
    }
}

int main(void) {
    int nums[] = {0, 1, 3, 50, 75};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int lower = 0;
    int upper = 99;

    Range* missing_ranges = NULL;
    int returnSize = 0;

    find_missing_ranges(nums, numsSize, lower, upper, &missing_ranges, &returnSize);

    if (missing_ranges != NULL) {
        for (int i = 0; i < returnSize; ++i) {
            printf("[%d, %d]\n", missing_ranges[i].start, missing_ranges[i].end);
        }
        free(missing_ranges);
        missing_ranges = NULL;
    }

    return 0;
}