#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int maxSubArrayLength(int *nums, int numsSize) {
    int max_so_far = INT_MIN, max_ending_here = 0, start = 0, end = 0, s = 0;
    for (int i = 0; i < numsSize; i++) {
        max_ending_here += nums[i];
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    return end - start + 1;
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Length of the subarray with maximum sum is %d\n", maxSubArrayLength(arr, n));
    return 0;
}