#include <stdio.h>
#include <stdlib.h>

struct Range {
    int start;
    int end;
};

struct Range* find_missing_ranges(const int* nums, int nums_size, int start, int end, int* result_size) {
    if (start > end) {
        *result_size = 0;
        return NULL;
    }

    int capacity = 16;
    struct Range* result = (struct Range*)malloc(capacity * sizeof(struct Range));
    if (!result) {
        *result_size = 0;
        return NULL;
    }

    *result_size = 0;
    int prev = start - 1;

    for (int i = 0; i <= nums_size; i++) {
        int curr;
        if (i < nums_size) {
            curr = nums[i];
        } else {
            curr = end + 1;
        }

        if (curr > prev + 1) {
            int range_start = prev + 1;
            int range_end = curr - 1;

            if (range_start < start) range_start = start;
            if (range_end > end) range_end = end;

            if (range_start <= range_end) {
                if (*result_size >= capacity) {
                    capacity *= 2;
                    struct Range* temp = (struct Range*)realloc(result, capacity * sizeof(struct Range));
                    if (!temp) {
                        free(result);
                        *result_size = 0;
                        return NULL;
                    }
                    result = temp;
                }
                result[*result_size].start = range_start;
                result[*result_size].end = range_end;
                (*result_size)++;
            }
        }
        prev = curr;
    }

    return result;
}

int main() {
    int nums[] = {2, 5, 10, 15};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int start = 0;
    int end = 20;
    int result_size = 0;

    struct Range* missing = find_missing_ranges(nums, nums_size, start, end, &result_size);

    if (missing) {
        for (int i = 0; i < result_size; i++) {
            printf("[%d, %d]\n", missing[i].start, missing[i].end);
        }
        free(missing);
    }

    return 0;
}