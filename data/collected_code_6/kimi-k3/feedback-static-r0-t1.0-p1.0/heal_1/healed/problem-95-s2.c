#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_sublist_length(const int *arr, int n, int target_sum) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    int min_length = INT_MAX;
    int current_sum = 0;
    int start = 0;
    
    for (int end = 0; end < n; end++) {
        current_sum += arr[end];
        
        while (current_sum >= target_sum && start <= end) {
            int current_length = end - start + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            current_sum -= arr[start];
            start++;
        }
    }
    
    if (min_length == INT_MAX) {
        return 0;
    }
    
    return min_length;
}

int main(void) {
    int arr[] = {2, 3, 1, 2, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target_sum = 7;
    
    int result = find_min_sublist_length(arr, n, target_sum);
    
    if (result > 0) {
        printf("Minimum length of sublist: %d\n", result);
    } else {
        printf("No sublist found with sum >= %d\n", target_sum);
    }
    
    return 0;
}