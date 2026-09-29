#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

void find_missing_ranges(int* nums, int nums_size, int lower, int upper, Range** result, int* return_size) {
    if (result == NULL || return_size == NULL) {
        return;
    }

    *return_size = 0;
    int capacity = 10;
    *result = (Range*)malloc(capacity * sizeof(Range));
    if (*result == NULL) {
        return;
    }

    long long next = lower;

    for (int i = 0; i < nums_size; i++) {
        if (nums[i] < next) {
            continue;
        }
        if (nums[i] == next) {
            next++;
            continue;
        }

        if (*return_size >= capacity) {
            capacity *= 2;
            Range* temp = (Range*)realloc(*result, capacity * sizeof(Range));
            if (temp == NULL) {
                free(*result);
                *result = NULL;
                *return_size = 0;
                return;
            }
            *result = temp;
        }

        (*result)[*return_size].start = (int)next;
        (*result)[*return_size].end = nums[i] - 1;
        (*return_size)++;
        next = (long long)nums[i] + 1;
    }

    if (next <= upper) {
        if (*return_size >= capacity) {
            capacity++;
            Range* temp = (Range*)realloc(*result, capacity * sizeof(Range));
            if (temp == NULL) {
                free(*result);
                *result = NULL;
                *return_size = 0;
                return;
            }
            *result = temp;
        }
        (*result)[*return_size].start = (int)next;
        (*result)[*return_size].end = upper;
        (*return_size)++;
    }
}

int main(void) {
    int nums[] = {0, 1, 3, 50, 75};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int lower = 0;
    int upper = 99;

    Range* missing_ranges = NULL;
    int return_size = 0;

    find_missing_ranges(nums, nums_size, lower, upper, &missing_ranges, &return_size);

    if (missing_ranges != NULL) {
        for (int i = 0; i < return_size; i++) {
            if (missing_ranges[i].start == missing_ranges[i].end) {
                printf("[%d]\n", missing_ranges[i].start);
            } else {
                printf("[%d, %d]\n", missing_ranges[i].start, missing_ranges[i].end);
            }
        }
        free(missing_ranges);
    }

    return 0;
}