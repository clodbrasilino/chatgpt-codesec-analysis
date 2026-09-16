#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range* find_missing_ranges(const int* nums, int nums_size, int start, int end, int* result_size) {
    *result_size = 0;

    if (nums_size == 0) {
        Range* result = (Range*)malloc(sizeof(Range));
        if (result == NULL) {
            return NULL;
        }
        result[0].start = start;
        result[0].end = end;
        *result_size = 1;
        return result;
    }

    int capacity = nums_size + 2;
    Range* result = (Range*)malloc(capacity * sizeof(Range));
    if (result == NULL) {
        return NULL;
    }

    int count = 0;

    if (nums[0] > start) {
        result[count].start = start;
        result[count].end = nums[0] - 1;
        count++;
    }

    for (int i = 1; i < nums_size; i++) {
        if (nums[i] > nums[i - 1] + 1) {
            result[count].start = nums[i - 1] + 1;
            result[count].end = nums[i] - 1;
            count++;
        }
    }

    if (nums[nums_size - 1] < end) {
        result[count].start = nums[nums_size - 1] + 1;
        result[count].end = end;
        count++;
    }

    *result_size = count;

    if (count == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void) {
    int nums[] = {1, 2, 4, 7};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int start = 0;
    int end = 9;
    int result_size = 0;

    Range* result = find_missing_ranges(nums, nums_size, start, end, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("[%d, %d]\n", result[i].start, result[i].end);
    }

    if (result != NULL) {
        free(result);
    }

    return 0;
}