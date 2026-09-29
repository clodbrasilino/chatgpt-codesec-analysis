#include <stdio.h>
#include <stdlib.h>

int *find_divisible(int *nums, int numsSize, int m, int n, int *returnSize) {
    int count = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] % m == 0 || nums[i] % n == 0) {
            ++count;
        }
    }
    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] % m == 0 || nums[i] % n == 0) {
            result[index++] = nums[i];
        }
    }
    *returnSize = count;
    return result;
}

int main() {
    int nums[] = {10, 15, 20, 25, 30};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int m = 5;
    int n = 3;
    int returnSize;
    int *result = find_divisible(nums, numsSize, m, n, &returnSize);
    if (result != NULL) {
        for (int i = 0; i < returnSize; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    }
    return 0;
}