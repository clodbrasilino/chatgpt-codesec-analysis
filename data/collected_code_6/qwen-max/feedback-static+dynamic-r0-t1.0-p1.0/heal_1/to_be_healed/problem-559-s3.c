#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int maxSubArraySum(int arr[], int n) {
    int max_so_far = INT_MIN, max_ending_here = 0;
    
    for (int i = 0; i < n; i++) {
        max_ending_here += arr[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    int max_sum = maxSubArraySum(arr, n);
    printf("Maximum contiguous sum is %d\n", max_sum);
    return 0;
}