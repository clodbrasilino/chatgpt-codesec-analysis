#include <stdio.h>
#include <limits.h>

int max_subarray_sum(int arr[], int n) {
    if (n <= 0) return 0;
    
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    
    for (int i = 0; i < n; i++) {
        max_ending_here += arr[i];
        
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
        
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }
    
    return max_so_far;
}

int main(void) {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = max_subarray_sum(arr, n);
    printf("Maximum contiguous sum is %d\n", result);
    
    return 0;
}