#include <stdio.h>
#include <stdlib.h>

int firstMissingPositive(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return 1;
    }

    int i = 0;
    while (i < numsSize) {
        int correct_pos = nums[i] - 1;
        if (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[correct_pos]) {
            int temp = nums[i];
            nums[i] = nums[correct_pos];
            nums[correct_pos] = temp;
        } else {
            i++;
        }
    }

    for (i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    return numsSize + 1;
}

int main(void) {
    int arr1[] = {1, 2, 0};
    int arr2[] = {3, 4, -1, 1};
    int arr3[] = {7, 8, 9, 11, 12};
    int arr4[] = {1};
    int arr5[] = {2, 1};

    printf("First missing positive: %d\n", firstMissingPositive(arr1, 3));
    printf("First missing positive: %d\n", firstMissingPositive(arr2, 4));
    printf("First missing positive: %d\n", firstMissingPositive(arr3, 5));
    printf("First missing positive: %d\n", firstMissingPositive(arr4, 1));
    printf("First missing positive: %d\n", firstMissingPositive(arr5, 2));

    return EXIT_SUCCESS;
}