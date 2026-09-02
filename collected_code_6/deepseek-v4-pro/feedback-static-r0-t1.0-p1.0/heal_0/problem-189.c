#include <stdio.h>
#include <stdlib.h>

int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] <= 0 || nums[i] > numsSize) {
            nums[i] = numsSize + 1;
        }
    }
    
    for (int i = 0; i < numsSize; i++) {
        int num = abs(nums[i]);
        if (num <= numsSize) {
            if (nums[num - 1] > 0) {
                nums[num - 1] = -nums[num - 1];
            }
        }
    }
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            return i + 1;
        }
    }
    
    return numsSize + 1;
}

int main(void) {
    int test1[] = {1, 2, 0};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("%d\n", firstMissingPositive(test1, size1));
    
    int test2[] = {3, 4, -1, 1};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("%d\n", firstMissingPositive(test2, size2));
    
    int test3[] = {7, 8, 9, 11, 12};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("%d\n", firstMissingPositive(test3, size3));
    
    int test4[] = {1};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("%d\n", firstMissingPositive(test4, size4));
    
    return 0;
}