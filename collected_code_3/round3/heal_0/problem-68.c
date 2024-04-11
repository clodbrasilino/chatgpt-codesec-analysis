#include <stdbool.h>
#include <stdio.h>

bool isMonotonic(int* nums, int numsSize) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 0; i < numsSize - 1; ++i) {
        if (nums[i] > nums[i+1]) {
            increasing = false;
        }
        if (nums[i] < nums[i+1]) {
            decreasing = false;
        }
    }

    return increasing || decreasing;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    if (isMonotonic(nums, numsSize)) {
        printf("The array is monotonic.\n");
    } else {
        printf("The array is not monotonic.\n");
    }

    return 0;
}