#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a == int_b) {
        return 0;
    }
    return (int_a < int_b) ? -1 : 1;
}

int* largest_divisible_subset(int* nums, int nums_size, int* return_size) {
    if (nums == NULL || return_size == NULL) {
        if (return_size != NULL) {
            *return_size = 0;
        }
        return NULL;
    }

    if (nums_size <= 0) {
        *return_size = 0;
        return NULL;
    }

    qsort(nums, (size_t)nums_size, sizeof(int), compare_ints);

    int *dp = (int*)malloc((size_t)nums_size * sizeof(int));
    int *parent = (int*)malloc((size_t)nums_size * sizeof(int));

    if (dp == NULL || parent == NULL) {
        free(dp);
        free(parent);
        *return_size = 0;
        return NULL;
    }

    int max_len = 0;
    int max_idx = -1;

    for (int i = 0; i < nums_size; i++) {
        dp[i] = 1;
        parent[i] = -1;
        
        for (int j = 0; j < i; j++) {
            if (nums[j] != 0 && nums[i] % nums[j] == 0) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
        
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_idx = i;
        }
    }

    int *result = (int*)malloc((size_t)max_len * sizeof(int));
    if (result == NULL) {
        free(dp);
        free(parent);
        *return_size = 0;
        return NULL;
    }

    int curr = max_idx;
    int idx = max_len - 1;
    
    while (curr != -1 && idx >= 0) {
        result[idx] = nums[curr];
        curr = parent[curr];
        idx--;
    }

    free(dp);
    free(parent);

    *return_size = max_len;
    return result;
}

int main(void) {
    int nums[] = {1, 2, 3, 4, 6, 8, 12, 24};
    int nums_size = (int)(sizeof(nums) / sizeof(nums[0]));
    int return_size = 0;
    
    int *result = largest_divisible_subset(nums, nums_size, &return_size);

    if (result != NULL) {
        for (int i = 0; i < return_size; i++) {
            printf("%d", result[i]);
            if (i < return_size - 1) {
                printf(" ");
            }
        }
        printf("\n");
        free(result);
    }

    return 0;
}