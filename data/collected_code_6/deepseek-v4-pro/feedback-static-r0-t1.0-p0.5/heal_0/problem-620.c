#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int largest_divisible_subset(int *nums, int nums_size, int *result) {
    if (nums == NULL || nums_size <= 0 || result == NULL) {
        return 0;
    }

    qsort(nums, nums_size, sizeof(int), compare_ints);

    int *dp = (int *)malloc(nums_size * sizeof(int));
    int *prev = (int *)malloc(nums_size * sizeof(int));
    if (dp == NULL || prev == NULL) {
        free(dp);
        free(prev);
        return 0;
    }

    for (int i = 0; i < nums_size; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }

    int max_index = 0;
    int max_size = 1;

    for (int i = 1; i < nums_size; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_size) {
            max_size = dp[i];
            max_index = i;
        }
    }

    int index = max_index;
    int count = 0;
    while (index != -1) {
        result[count++] = nums[index];
        index = prev[index];
    }

    for (int i = 0; i < count / 2; i++) {
        int temp = result[i];
        result[i] = result[count - 1 - i];
        result[count - 1 - i] = temp;
    }

    free(dp);
    free(prev);
    return count;
}

int main(void) {
    int nums[] = {1, 2, 4, 8, 3, 6, 12};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int *result = (int *)malloc(nums_size * sizeof(int));
    if (result == NULL) {
        return 1;
    }

    int result_size = largest_divisible_subset(nums, nums_size, result);

    printf("Largest divisible subset size: %d\n", result_size);
    printf("Subset: ");
    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}