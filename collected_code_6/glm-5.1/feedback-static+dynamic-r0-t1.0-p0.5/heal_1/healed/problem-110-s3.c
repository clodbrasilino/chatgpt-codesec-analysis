#include <stdio.h>
#include <stdlib.h>

struct Range {
    int start;
    int end;
};

struct Range* find_missing_ranges(const int* nums, int nums_size, int start, int end, int* result_size) {
    if (result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (start > end) {
        return NULL;
    }

    int capacity = 2;
    struct Range* result = (struct Range*)malloc(capacity * sizeof(struct Range));
    if (result == NULL) {
        return NULL;
    }

    int current = start;

    for (int i = 0; i < nums_size; i++) {
        if (nums[i] < current) {
            continue;
        }

        if (nums[i] > end) {
            break;
        }

        if (nums[i] > current) {
            if (*result_size >= capacity) {
                capacity *= 2;
                struct Range* temp = (struct Range*)realloc(result, capacity * sizeof(struct Range));
                if (temp == NULL) {
                    free(result);
                    *result_size = 0;
                    return NULL;
                }
                result = temp;
            }
            result[*result_size].start = current;
            result[*result_size].end = nums[i] - 1;
            (*result_size)++;
        }

        current = nums[i] + 1;
    }

    if (current <= end) {
        if (*result_size >= capacity) {
            capacity += 1;
            struct Range* temp = (struct Range*)realloc(result, capacity * sizeof(struct Range));
            if (temp == NULL) {
                free(result);
                *result_size = 0;
                return NULL;
            }
            result = temp;
        }
        result[*result_size].start = current;
        result[*result_size].end = end;
        (*result_size)++;
    }

    return result;
}

int main() {
    int nums[] = {1, 3, 5, 7};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int start = 0;
    int end = 10;
    int result_size = 0;

    struct Range* missing = find_missing_ranges(nums, nums_size, start, end, &result_size);

    if (missing != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("[%d, %d]\n", missing[i].start, missing[i].end);
        }
        free(missing);
    }

    return 0;
}