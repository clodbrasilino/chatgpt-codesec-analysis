#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int* find_largest_divisible_subset(int* nums, int nums_size, int* return_size) {
    if (nums == NULL || nums_size <= 0 || return_size == NULL) {
        if (return_size != NULL) {
            *return_size = 0;
        }
        return NULL;
    }

    qsort(nums, (size_t)nums_size, sizeof(int), compare_ints);

    int* dp = (int*)malloc((size_t)nums_size * sizeof(int));
    if (dp == NULL) {
        *return_size = 0;
        return NULL;
    }

    int* parent = (int*)malloc((size_t)nums_size * sizeof(int));
    if (parent == NULL) {
        free(dp);
        *return_size = 0;
        return NULL;
    }

    int max_len = 1;
    int max_idx = 0;

    for (int i = 0; i < nums_size; ++i) {
        dp[i] = 1;
        parent[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_idx = i;
        }
    }

    int* result = (int*)malloc((size_t)max_len * sizeof(int));
    if (result == NULL) {
        free(dp);
        free(parent);
        *return_size = 0;
        return NULL;
    }

    int current_idx = max_idx;
    for (int i = max_len - 1; i >= 0; --i) {
        result[i] = nums[current_idx];
        current_idx = parent[current_idx];
    }

    free(dp);
    free(parent);

    *return_size = max_len;
    return result;
}

int main(void) {
    int nums[] = {1, 2, 4, 8, 9, 72};
    int nums_size = (int)(sizeof(nums) / sizeof(nums[0]));
    int return_size = 0;

    int* result = find_largest_divisible_subset(nums, nums_size, &return_size);

    if (result != NULL) {
        for (int i = 0; i < return_size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}