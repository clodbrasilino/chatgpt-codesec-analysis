#include <stdio.h>
#include <stdlib.h>

long long maxProduct(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    long long max_so_far = nums[0];
    long long min_so_far = nums[0];
    long long result = max_so_far;

    for (int i = 1; i < numsSize; i++) {
        long long curr = nums[i];
        
        long long temp_max = max_so_far * curr;
        long long temp_min = min_so_far * curr;

        long long current_max = curr > temp_max ? curr : temp_max;
        current_max = current_max > temp_min ? current_max : temp_min;

        long long current_min = curr < temp_max ? curr : temp_max;
        current_min = current_min < temp_min ? current_min : temp_min;

        max_so_far = current_max;
        min_so_far = current_min;

        if (max_so_far > result) {
            result = max_so_far;
        }
    }

    return result;
}

int main() {
    int nums1[] = {2, 3, -2, 4};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("%lld\n", maxProduct(nums1, size1));

    int nums2[] = {-2, 0, -1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("%lld\n", maxProduct(nums2, size2));

    return 0;
}