#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
long long maxProduct(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    long long max_so_far = nums[0];
    long long min_so_far = nums[0];
    long long result = nums[0];

    for (int i = 1; i < numsSize; i++) {
        long long curr = nums[i];
        
        long long temp_max = max_so_far * curr;
        long long temp_min = min_so_far * curr;

        if (curr > temp_max) {
            max_so_far = curr > temp_min ? curr : temp_min;
        } else {
            max_so_far = temp_max > temp_min ? temp_max : temp_min;
        }

        if (curr < temp_max) {
            min_so_far = curr < temp_min ? curr : temp_min;
        } else {
            min_so_far = temp_max < temp_min ? temp_max : temp_min;
        }

        if (max_so_far > result) {
            result = max_so_far;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {2, 3, -2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    long long result = maxProduct(arr, n);
    printf("%lld\n", result);
    return 0;
}