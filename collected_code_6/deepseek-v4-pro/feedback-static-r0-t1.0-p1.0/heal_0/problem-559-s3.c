#include <stdio.h>
#include <limits.h>

int max_subarray_sum(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }
    
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    
    for (int i = 0; i < n; i++) {
        max_ending_here = max_ending_here + arr[i];
        
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
    
    int max_sum = max_subarray_sum(arr, n);
    printf("Maximum contiguous sum is %d\n", max_sum);
    
    int arr2[] = {-1, -2, -3, -4};
    n = sizeof(arr2) / sizeof(arr2[0]);
    max_sum = max_subarray_sum(arr2, n);
    printf("Maximum contiguous sum is %d\n", max_sum);
    
    struct test {
        int *arr;
        int n;
        int expected;
    };
    
    struct test tests[] = {
        {(int[]){1, 2, 3, 4}, 4, 10},
        {(int[]){-1, 1, -1, 1}, 4, 1},
        {(int[]){5, -1, 5}, 3, 9},
        {(int[]){-5, -4, -3}, 3, -3}
    };
    
    for (int i = 0; i < 4; i++) {
        int result = max_subarray_sum(tests[i].arr, tests[i].n);
        printf("Test %d: got %d, expected %d\n", i + 1, result, tests[i].expected);
    }
    
    return 0;
}