#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    int l = 0, r = numsSize - 1;
    while (l < r) {
        int mid = l + ((r - l) / 2);
        if (nums[mid] == nums[mid ^ 1]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return nums[l];
}

int main() {
    int nums[] = {1,1,2,3,3,4,4,8,8};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = singleNumber(nums, numsSize);
    printf("%d\n", result);
    return 0;
}