#include <stdio.h>
#include <stdlib.h>

int longestConsecutive(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return 0;
    }

    int cmp(const void* a, const void* b) {
        long long diff = (long long)(*(int*)a) - (long long)(*(int*)b);
        if (diff < 0) return -1;
        if (diff > 0) return 1;
        return 0;
    }

    qsort(nums, numsSize, sizeof(int), cmp);

    int max_len = 1;
    int current_len = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            continue;
        } else if (nums[i] == nums[i - 1] + 1) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 1;
        }
    }

    return max_len;
}

int main() {
    int arr1[] = {100, 4, 200, 1, 3, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = longestConsecutive(arr1, size1);
    printf("%d\n", res1);

    int arr2[] = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = longestConsecutive(arr2, size2);
    printf("%d\n", res2);

    int arr3[] = {};
    int res3 = longestConsecutive(arr3, 0);
    printf("%d\n", res3);

    return 0;
}