#include <stdio.h>

int maxSubarrayLength(int arr[], int n) {
    int max_len = 0;
    int curr_len = 0;
    int max_sum = 0;
    int curr_sum = 0;
    int start = 0;
    int end = 0;
    
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        curr_sum = curr_sum + arr[i];
        curr_len++;
        
        if (curr_sum > max_sum) {
            max_sum = curr_sum;
            max_len = curr_len;
            end = i;
        }
        
        if (curr_sum < 0) {
            curr_sum = 0;
            curr_len = 0;
            start = i + 1;
        }
    }
    
    printf("Start index: %d\n", start);
    printf("End index: %d\n", end);
    
    return max_len;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_len = maxSubarrayLength(arr, n);
    
    printf("Length of subarray with maximum sum: %d\n", max_len);
    
    return 0;
}